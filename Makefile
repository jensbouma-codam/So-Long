# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbouma <jbouma@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/10 14:09:40 by jbouma        #+#    #+#                  #
#    Updated: 2023/05/15 23:22:10 by jensbouma     ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Program Name(s)
NAME		=	so_long

# Compiler Settings
CC 			:= gcc
GLFW		:= -framework Cocoa -framework OpenGL -framework IOKit
# CFLAGS		+= -O3
# CFLAGS		+= -Werror
# CFLAGS		+= -Wall -Wextra 
# -Wunreachable-code 
# CFLAGS		+= -lglfw
# Headers
INC 		= -I include 
# -I /opt/homebrew/Cellar/glfw/3.3.8/include

# Set build directories
BUILDDIR	= ./build/
TARGET		= bin/$<

# Sources
SRCDIR		= 	src
FILES		= 	main.c		\
				globals.c	\
				files.c		\
				maps.c		\
				hooks.c		\
				player_move.c	\
				array_helpers.c	\
				error_handler.c	\
	
SOURCES		=	${addprefix $(SRCDIR)/, $(FILES)}

# Libraries
LIBDIR		=	lib

LIBS		=	libFT			\
				libglfw3		\
				libmlx42

BREW		=	glfw			\

# TEXTURES	=	./assets/Platformer_Art_Complete_Pack.zip	\

HEADERS		=	$(LIBS:%=-I $(LIBDIR)/%/include)
# -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"	\
# -lglfw
GLFW3_LIBRARY 	= 	$(LIBDIR)/libglfw3/src/lglfw3.a
GLFW3_INCLUDE 	= 	$(LIBDIR)/libglfw3/include

EXTRA 			=	-D GLFW3_INCLUDE_PATH=$(GLFW3_INCLUDE) -D GLFW3_LIBRARY=$(GLFW3_LIBRARY)
LIBARIES		=	${addprefix $(LIBDIR)/, $(LIBS)} 
LIBARIES_AFILES	=	${addprefix $(BUILDDIR), ${addsuffix .a, $(LIBS)}}

# Objects
OBJECTS		= $(SOURCES:%.c=$(BUILDDIR)%.o)

# Colors
ifneq (,$(findstring xterm,${TERM}))
	BLACK		:= $(shell tput -Txterm setaf 0)
	RED			:= $(shell tput -Txterm setaf 1)
	GREEN		:= $(shell tput -Txterm setaf 2)
	YELLOW		:= $(shell tput -Txterm setaf 3)
	LIGHTPURPLE	:= $(shell tput -Txterm setaf 4)
	PURPLE		:= $(shell tput -Txterm setaf 5)
	BLUE		:= $(shell tput -Txterm setaf 6)
	WHITE		:= $(shell tput -Txterm setaf 7)
	RESET		:= $(shell tput -Txterm sgr0)
	RETURN		:= "\033[0K\n"
endif

P_OK			= printf "%-25.25s%s%s\n" "$@${GREEN}" "Norm OK" "${RESET}"
P_KO			= printf "%-25.25s%s%s\n" "$@${RED}" "Norm KO" "${RESET}"

# Rules
all: $(NAME)
	@[ -f ./textures/license.txt ] && printf "%-25.25s%s\n" "Textures$(GREEN)" "Already installed $(RESET)" 	\
	|| (unzip assets/Platformer_Art_Complete_Pack.zip -d ./textures > /dev/null && printf "%-25.25s%s\n" "Textures$(GREEN)" "Installed $(RESET)") 
	@mkdir -p ./bin
# @[ -f /opt/homebrew/Cellar/glfw/3.3.8/lib/libglfw.3.3.dylib ] 																		\
# 	&& $(CC) $(CFLAGS) $(HEADERS) -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/" $(INC) $(OBJECTS) $(LIBARIES_AFILES) -o $(TARGET) \
# 	|| (printf "%s\n" "$(RED)GLFW not installed with homebrew, trying to compile with lglfw3 $(RESET)"								\
# 	&& 
	@$(CC) $(CFLAGS) $(GLFW) $(HEADERS) $(INC) $(OBJECTS) $(LIBARIES_AFILES) -o $(TARGET)
	@printf "%-25.25s%s\n" "Executable $(GREEN)" "$< Created $(RESET)"
	@printf "%-25.25s%s\n" "Flags $(YELLOW)" "$(CFLAGS) $(RESET)"
	@printf "\n🙏 $(GREEN)Complete $(RESET)\n"

$(BUILDDIR)%.o:%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ 
	@norminette -R CheckForbiddenSourceHeader $< > /dev/null && printf "%-25.25s%s\n" "Build${GREEN}" "$(notdir $<)" ||  printf "%-25.25s%s\n" "Build${RED}" "$(notdir $<)"
	@printf "${RESET}"

$(LIBS):
	@mkdir -p $(BUILDDIR)
# @printf "%-25.25s%s\n" "Submodule${YELLOW}" "$@$(RESET)"
	@git submodule update --init lib/$@ > /dev/null && printf "%-25.25s%s\n" "Submodule${GREEN}" "$@$(RESET)" || printf "%-25.25s%s\n" "Submodule${RED}" "$@$(RESET)"
# @norminette -R CheckForbiddenSourceHeader $(LIBDIR)/$@/include $(LIBDIR)/$@/src > /dev/null && $(P_OK) || { $(P_KO); }
	@if [[ "$@" == "libmlx42" ]]; then \
		[ -f ./$(LIBDIR)/$@/CMakeLists.txt ] && (cmake $(LIBDIR)/$@  $(EXTRA) -B $(BUILDDIR)$@ 2>&1 > /dev/null && make -C $(BUILDDIR)$@ > /dev/null && printf "%-25.25s%s\n" "$@$(GREEN)" "OK$(RESET)" || printf "%-25.25s%s\n" "$@$(RED)" "Error$(RESET)")  || printf ""|| printf ""; \
	else	\
		[ -f ./$(LIBDIR)/$@/CMakeLists.txt ] && (cmake $(LIBDIR)/$@ -B $(BUILDDIR)$@ 2>&1 > /dev/null && make -C $(BUILDDIR)$@ > /dev/null && printf "%-25.25s%s\n" "$@$(GREEN)" "OK$(RESET)" || printf "%-25.25s%s\n" "$@$(RED)" "Error$(RESET)")  || printf ""|| printf ""; \
	fi
	@[ -f ./$(LIBDIR)/$@/Makefile ] && (make -C $(LIBDIR)/$@ > /dev/null && printf "%-25.25s%s\n" "$@$(GREEN)" "OK$(RESET)" || printf "%-25.25s%s\n" "$@$(RED)" "Error$(RESET)")  || printf ""
	@[ -f $(BUILDDIR)$@/$@.a ] && cp -p $(BUILDDIR)$@/$@.a $(BUILDDIR) || printf ""
	@[ -f $(BUILDDIR)$@/src/$@.a ] && cp -p $(BUILDDIR)$@/src/$@.a $(BUILDDIR) || printf ""
	@[ -f $(LIBDIR)/$@/$@.a ] && cp -p $(LIBDIR)/$@/$@.a $(BUILDDIR) || printf ""


$(NAME): $(LIBS) $(OBJECTS)
	@make norm 2> /dev/null && $(P_OK) || { $(P_KO);}
	
$(BREW):
	@[ -f /opt/homebrew/Cellar/glfw/3.3.8/lib/libglfw.3.3.dylib ]										\
		&& printf "%-25.25s%s\n" "Brew $(BREW)$(GREEN)" "Already installed $(RESET)"								\
		|| (brew install $(BREW) >/dev/null && printf "%-25.25s%s\n" "Brew$(GREEN)" "$(BREW) Installed$(RESET)" || printf "%-25.25s%s\n"  "Brew$(RED)" "GLFW Failed$(RESET)")

leaks: CFLAGS += -g -D DEBUG=3
leaks: re
	@printf "$(RED)Compiled in debug / leaks mode!!!$(RESET)"

debug: CFLAGS += -g -fsanitize=address -D DEBUG=1
debug: all
	@printf "$(RED)Compiled in debug / fsanitize=adress mode!!!$(RESET)\n\n"
	@./bin/$(NAME)

clean:
	@rm -rf $(BUILDDIR)
	@rm -rf $(LIBDIR)/*/*.a

fclean: clean
	@rm -rf $(LIBDIR)/*/build
	@rm -rf ./textures
	@rm -rf bin

re: fclean all

norm: $(SOURCES)
	@norminette -R CheckForbiddenSourceHeader $^ include > /dev/null && exit 0 || exit 1

.PHONY: CFLAGS all clean fclean re
