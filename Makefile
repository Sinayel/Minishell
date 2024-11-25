CC = cc

CFLAGS = -Wall -Wextra -Werror -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline -g3

INCLUDE = -I ./include -I ./Libft
DIRLIB = ./libft/
FILELIB = libft.a
NAMELFT = $(addprefix $(DIRLIB), $(FILELIB))

MAKEFLAGS += --no-print-directory
RM = rm -f
VGCORE_FILES = vgcore.*
NAME = minishell

DOLLAR_SRC =  srcs/parsing/dollar/pid.c \
			  srcs/parsing/dollar/dollar.c \
			  srcs/parsing/dollar/len_dollar.c \
			  srcs/parsing/dollar/code_error.c \

PARSING_SRC = srcs/parsing/token/id_token.c \
			  srcs/parsing/token/tokenization.c \
			  srcs/parsing/check.c \
			  srcs/parsing/path.c \
			  srcs/parsing/parsing.c

BUILTIN_SRC = srcs/builtins/env/env.c \
			  srcs/builtins/env/create_env.c \
			  srcs/builtins/echo/echo.c \
			  srcs/builtins/pwd/pwd.c \
			  srcs/builtins/cd/cd.c \
			  srcs/builtins/export/export.c \

UTILS_SRC = srcs/utils/utils.c \
			srcs/utils/free.c \
			srcs/utils/utils_dollar.c \
			srcs/utils/for_list.c \
			srcs/utils/utils_token.c \
			srcs/utils/ft_split.c \
			srcs/utils/ft_strtol.c \
			srcs/error/msg.c \

MINISHELL_SRC = main.c $(PARSING_SRC) $(UTILS_SRC) $(BUILTIN_SRC) $(DOLLAR_SRC)

ASCII_LOGO = -e "\
	███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
	████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
	██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
	██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"

all: $(NAMELFT) $(NAME)

$(NAMELFT):
	@echo "Compilation de la libft..."
	@$(MAKE) -C $(DIRLIB)

$(NAME): $(MINISHELL_SRC) $(NAMELFT)
	@echo -e '\033[35mCreating Minishell... 🕗\n'
	@echo $(ASCII_LOGO)
	@$(CC) $(MINISHELL_SRC) $(NAMELFT) $(CFLAGS) $(LDFLAGS) $(INCLUDE) -o $(NAME)
	@echo -e '\033[33;32mMinishell created ! 🎉\033[0m'

clean:
	@$(MAKE) -C $(DIRLIB) clean
	@$(RM) $(NAME)
	@echo -e '\033[0;31mMinishell deleted ! 🛑'

fclean: clean
	@$(MAKE) -C $(DIRLIB) fclean
	@$(RM) $(VGCORE_FILES)

re: fclean all

.PHONY: all clean fclean re
