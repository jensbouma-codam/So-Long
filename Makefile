# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbouma <jbouma@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/10 14:09:40 by jbouma        #+#    #+#                  #
#    Updated: 2023/05/15 23:55:14 by jensbouma     ########   odam.nl          #
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
# CFLAGS		+= -Wunreachable-code 

# Headers
INC 		= -I include 

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
	RETURN		:= "\033[0K\n"
endif

PRT 		:= printf "%-25.25s%s\n"

P_OK			= printf "%-25.25s%s%s\n" "$@${GREEN}" "Norm OK" "${RESET}"
P_KO			= printf "%-25.25s%s%s\n" "$@${RED}" "Norm KO" "${RESET}"

# Rules
all: $(NAME)
	@[ -f ./textures/license.txt ]														\
		&& $(PRT) "Textures$(GREEN)" "Already installed $(RESET)"						\
		|| (unzip assets/Platformer_Art_Complete_Pack.zip -d ./textures > /dev/null		\
		&& $(PRT) "Textures$(GREEN)" "Installed $(RESET)")
	@mkdir -p ./bin
	@$(CC) $(CFLAGS) $(GLFW) $(HEADERS) $(INC) $(OBJECTS) $(LIBARIES_AFILES) -o $(TARGET)
	@$(PRT) "Executable $(GREEN)" "$< Created $(RESET)"
	@$(PRT) "Flags $(YELLOW)" "$(CFLAGS) $(RESET)"
	@printf "\n🙏 $(GREEN)Complete $(RESET)\n"

$(BUILDDIR)%.o:%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ 
	@norminette -R CheckForbiddenSourceHeader $< > /dev/null 				\
		&& $(PRT) "Build${GREEN}" "$(notdir $<)${RESET}" 					\
		||  $(PRT) "Build${RED}" "$(notdir $<)${RESET}"
$(LIBS):
	@mkdir -p $(BUILDDIR)
	@git submodule update --init lib/$@ > /dev/null							\
		&& $(PRT) "Submodule${GREEN}" "$@$(RESET)"							\
		|| $(PRT) "Submodule${RED}" "$@$(RESET)"
# @norminette -R CheckForbiddenSourceHeader $(LIBDIR)/$@/include $(LIBDIR)/$@/src > /dev/null && $(P_OK) || { $(P_KO); }
	@if [[ "$@" == "libmlx42" ]]; then										\
		[ -f ./$(LIBDIR)/$@/CMakeLists.txt ]								\
		&& (cmake $(LIBDIR)/$@  $(EXTRA) -B $(BUILDDIR)$@ 2>&1 > /dev/null	\
			&& make -C $(BUILDDIR)$@ > /dev/null							\
			&& $(PRT) "$@$(GREEN)" "Compiled$(RESET)"						\
			|| $(PRT) "$@$(RED)" "Error$(RESET)")							\
		|| break;														\
	else [ -f ./$(LIBDIR)/$@/CMakeLists.txt ]								\
		&& (cmake $(LIBDIR)/$@ -B $(BUILDDIR)$@ 2>&1 > /dev/null			\
			&& make -C $(BUILDDIR)$@ > /dev/null							\
			&& $(PRT) "$@$(GREEN)" "Compiled$(RESET)"						\
			|| $(PRT) "$@$(RED)" "Error$(RESET)")							\
		|| break; fi
	@[ -f ./$(LIBDIR)/$@/Makefile ]											\
		&& (make -C $(LIBDIR)/$@ > /dev/null								\
			&& $(PRT) "$@$(GREEN)" "OK$(RESET)"								\
			|| $(PRT) "$@$(RED)" "Error$(RESET)")							\
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
