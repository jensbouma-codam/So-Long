# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbouma <jbouma@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/10 14:09:40 by jbouma        #+#    #+#                  #
#    Updated: 2023/05/13 13:51:15 by jensbouma     ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# Program Name(s)
NAME		=	so_long

# Compiler Settings
CC 			:= gcc
# CFLAGS 		:= -framework Cocoa -framework OpenGL -framework IOKit
# CFLAGS		+= -O3
# CFLAGS		+= -Werror
# CFLAGS		+= -Wall -Wextra 
# -Wunreachable-code 
# CFLAGS		+= -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
# Headers
INC 		= -I include -I /opt/homebrew/Cellar/glfw/3.3.8/include

# Set build directories
BUILDDIR	= ./build/
TARGET		= bin/$<

# Sources
SRCDIR		= 	src
FILES		= 	main.c		\
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
				libmlx42		\

BREW		=	glfw			\

TEXTURES	=	./assets/Platformer_Art_Complete_Pack.zip	\

HEADERS		=	$(LIBS:%=-I $(LIBDIR)/%/include)	\
				-lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"	\

LIBARIES		=	${addprefix $(LIBDIR)/, $(LIBS)}
LIBARIES_AFILES	=	${addprefix $(BUILDDIR)/, ${addsuffix .a, $(LIBS)}}

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

P_OK			= printf "$@ \t\t%s\033[0K\n" "${GREEN}Norm OK${RESET}"
P_KO			= printf "$@ \t\t%s\033[0K\n" "${RED}Norm KO${RESET}"
P_NL			= printf " \n"

# Rules
all: $(NAME)
	@mkdir -p ./bin
	@$(CC) $(CFLAGS) $(HEADERS) $(INC) $(OBJECTS) $(LIBARIES_AFILES) -o $(TARGET)
	@printf "Executable \t$< \033[0K\n"
	@printf "\n$(YELLOW)Compiled with flags: $(CFLAGS)\n"
	@printf "\n🙏 $(GREEN)Complete $(RESET)\t\033[0K\n"

$(BUILDDIR)%.o:%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ 
	@norminette -R CheckForbiddenSourceHeader $< > /dev/null && printf "Build \t\t${GREEN}$(notdir $<) \033[0K\r\n" ||  printf "Build \t\t${RED}$(notdir $<) \033[0K\r\n"
	@printf "${RESET}"

$(LIBS): $(BREW) $(TEXTURES)
	@mkdir -p $(BUILDDIR)
	@printf "Submodule \t$@ \033[0K\r\n"
	@git submodule update --init
	@norminette -R CheckForbiddenSourceHeader $(LIBDIR)/$@/include $(LIBDIR)/$@/src > /dev/null && $(P_OK) || { $(P_KO); }
	@[ -f ./$(LIBDIR)/$@/CMakeLists.txt ] && cmake -D DEBUG=1 $(LIBDIR)/$@ -B $(BUILDDIR)$@ > /dev/null && make -C $(BUILDDIR)$@ > /dev/null || echo
	@[ -f ./$(LIBDIR)/$@/Makefile ] && make -C $(LIBDIR)/$@ || echo
	@[ -f $(BUILDDIR)$@/$@.a ] && cp -p $(BUILDDIR)$@/$@.a $(BUILDDIR) || echo
	@[ -f $(LIBDIR)/$@/$@.a ] && cp -p $(LIBDIR)/$@/$@.a $(BUILDDIR) || echo

$(BREW):
	@brew install $@ 2> /dev/null && printf "BREW \t\t${GREEN}$@$(RESET) \033[0K\r\n" || printf "BREW\t\t${RED}$@$(RESET) \033[0K\r\n"

$(TEXTURES):
	unzip $@ -d ./textures

$(NAME): $(LIBS) $(OBJECTS)
	@make norm 2> /dev/null && $(P_OK) || { $(P_KO);}
	

leaks: CFLAGS += -g -D DEBUG=3
leaks: re
	@printf "$(RED)Compiled in debug / leaks mode!!!$(RESET)"

debug: CFLAGS += -g -fsanitize=address -D DEBUG=1
debug: re
	@printf "$(RED)Compiled in debug / fsanitize=adress mode!!!$(RESET)"

clean:
	@rm -rf $(BUILDDIR)
	@rm -rf $(LIBDIR)/*/*.a

fclean: clean
	@rm -rf $(LIBDIR)/*/build
	@rm -rf bin

re: fclean all

norm: $(SOURCES)
	@norminette -R CheckForbiddenSourceHeader $^ include > /dev/null && exit 0 || exit 1

.PHONY: CFLAGS all clean fclean re
