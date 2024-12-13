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

DOLLAR_SRC =  srcs/parsing/dollar/dollar.c \
			  srcs/parsing/dollar/len_dollar.c \
			  srcs/parsing/dollar/code_error.c \

PARSING_SRC = srcs/parsing/token/id_token.c \
			  srcs/parsing/token/tokenization.c \
			  srcs/parsing/token/return_quoted_value.c \
			  srcs/parsing/check.c \
			  srcs/parsing/path.c \
			  srcs/parsing/parsing.c \
			  srcs/exec/exec.c \

BUILTIN_SRC = srcs/builtins/env/env.c \
			  srcs/builtins/env/create_env.c \
			  srcs/builtins/echo/ft_echo.c \
			  srcs/builtins/pwd/pwd.c \
			  srcs/builtins/cd/cd.c \
			  srcs/builtins/cd/pwd_option.c \
			  srcs/builtins/cd/option_cd.c \
			  srcs/builtins/unset/unset.c \
			  srcs/builtins/unset/utils_unset.c \
			  srcs/builtins/unset/for_unset.c \
			  srcs/builtins/export/export.c \
			  srcs/builtins/export/print_export.c \
			  srcs/builtins/export/replace_env.c \
			  srcs/builtins/export/verif_if_export.c \
			  srcs/builtins/export/big_export.c \
			  srcs/builtins/export/big_big_export.c \
			  srcs/builtins/export/copy_to_export.c \
			  srcs/builtins/export/env_to_export.c \
			  srcs/builtins/export/export_create.c \
			  srcs/error/ft_exit.c \

UTILS_SRC = srcs/utils/utils.c \
			srcs/utils/free.c \
			srcs/utils/utils_dollar.c \
			srcs/utils/for_list.c \
			srcs/utils/utils_token.c \
			srcs/utils/signal.c \
			srcs/utils/utils_token2.c \
			srcs/utils/ft_exit_utils.c \
			srcs/utils/ft_split.c \
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