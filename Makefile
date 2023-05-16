# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbouma <jbouma@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/10 14:09:40 by jbouma        #+#    #+#                  #
#    Updated: 2023/05/16 16:10:19 by jbouma        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Program Name(s)
NAME		=	so_long

# Compiler Settings
CC 			:= gcc

UNAME_S 	:= $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	GLFW		:= -ldl -pthread -lm
endif
ifeq ($(UNAME_S),Darwin)
	GLFW		:= -framework Cocoa -framework OpenGL -framework IOKit
endif

# CFLAGS		+= -O3
CFLAGS		+= -Werror
CFLAGS		+= -Wall -Wextra
# CFLAGS		+= -Wunreachable-code 

# Headers
INC 		= -I include 

# Set build directories
BUILDDIR	= build/
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

HEADERS		=	$(LIBS:%=-I $(LIBDIR)/%/include)

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
endif
	RETURN		:= "\033[0K\n"
P				:= printf "%-25.25s%s\n"
P_OK			= $(P) "$@${GREEN}" "Norm OK" "${RESET}"
P_KO			= $(P) "$@${RED}" "Norm KO" "${RESET}"

# Rules
all: $(NAME)
	@[ -f textures/license.txt ]														\
		&& $(P) "Textures$(GREEN)" "Already installed $(RESET)"							\
		|| (unzip assets/Platformer_Art_Complete_Pack.zip -d textures > /dev/null		\
		&& $(P) "Textures$(GREEN)" "Installed $(RESET)")
	@mkdir -p bin
	@$(CC) $(CFLAGS) $(GLFW) $(INC) $(HEADERS) $(OBJECTS) $(LIBARIES_AFILES) -o $(TARGET)
	@$(P) "Executable $(GREEN)" "$< Created $(RESET)"
	@$(P) "Flags $(YELLOW)" "$(CFLAGS) $(RESET)"
	@make norm 2> /dev/null && ($(P) "Norminette$(GREEN)" "OK$(RESET)" && printf "\n🙏 $(GREEN)Complete $(RESET)\n") || $(P) "Norminette$(RED)" "KO$(RESET)"

$(BUILDDIR)%.o:%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
ifneq ($(UNAME_S),Linux)
	@norminette -R CheckForbiddenSourceHeader $< > /dev/null 				\
		&& $(P) "Build${GREEN}" "$(notdir $<)${RESET}" 						\
		|| $(P) "Build${RED}" "$(notdir $<)${RESET}"
endif

$(LIBS):
	@mkdir -p $(BUILDDIR)
	@git submodule update --init lib/$@ 2>&1 > /dev/null					\
		&& $(P) "Submodule${GREEN}" "$@$(RESET)"							\
		|| $(P) "Submodule${RED}" "$@$(RESET)"
# @norminette -R CheckForbiddenSourceHeader $(LIBDIR)/$@/include $(LIBDIR)/$@/src > /dev/null && $(P_OK) || { $(P_KO); }
	@[ -f $(LIBDIR)/$@/include/MLX42/MLX42.h ]								\
		&& (cmake $(LIBDIR)/$@  $(EXTRA) -B $(BUILDDIR)$@ 2>&1 > /dev/null	\
			&& make -C $(BUILDDIR)$@ > /dev/null							\
			&& $(P) "$@$(GREEN)" "Compiled$(RESET)"							\
			|| $(P) "$@$(RED)" "Error$(RESET)")								\
		|| [ -f $(LIBDIR)/$@/CMakeLists.txt ]								\
			&& (cmake $(LIBDIR)/$@ -B $(BUILDDIR)$@ 2>&1 > /dev/null		\
				&& make -C $(BUILDDIR)$@ > /dev/null						\
				&& $(P) "$@$(GREEN)" "Compiled$(RESET)"						\
				|| $(P) "$@$(RED)" "Error$(RESET)")							\
			|| break
	@[ -f $(LIBDIR)/$@/Makefile ]											\
		&& (make -C $(LIBDIR)/$@ > /dev/null								\
			&& $(P) "$@$(GREEN)" "OK$(RESET)"								\
			|| $(P) "$@$(RED)" "Error$(RESET)")								\
		|| break
	@[ -f $(BUILDDIR)$@/$@.a ]												\
		&& cp -p $(BUILDDIR)$@/$@.a $(BUILDDIR)								\
		|| break
	@[ -f $(BUILDDIR)$@/src/$@.a ]											\
		&& cp -p $(BUILDDIR)$@/src/$@.a $(BUILDDIR)							\
		|| break
	@[ -f $(LIBDIR)/$@/$@.a ]												\
		&& cp -p $(LIBDIR)/$@/$@.a $(BUILDDIR)								\
		|| break


$(NAME): $(LIBS) $(OBJECTS)
	@make norm 2> /dev/null && $(P_OK) || { $(P_KO);}

leaks: CFLAGS += -g -D DEBUG=3
leaks: all
	@printf "$(RED)Compiled in debug / leaks mode!!!$(RESET)"

debug: CFLAGS += -g -fsanitize=address -D DEBUG=1
debug: all
	@printf "$(RED)Compiled in debug / fsanitize=adress mode!!!$(RESET)\n\n"
	@bin/$(NAME)

clean:
	@rm -rf $(BUILDDIR)
	@rm -rf $(LIBDIR)/*/*.a

fclean: clean
	@rm -rf $(LIBDIR)/*/build
	@rm -rf textures
	@rm -rf bin

re: fclean all

norm: $(SOURCES)
ifneq ($(UNAME_S),Linux)
	@norminette -R CheckForbiddenSourceHeader $^ include 2>&1 > /dev/null && exit 0 || exit 1
else
	@echo "Norminette not available on Linux" && exit 0
endif


.PHONY: CFLAGS all clean fclean re
