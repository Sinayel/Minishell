CC = cc

CFLAGS = -Wall -Wextra -Werror -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline -g3

INCLUDE = -I ./include -I ./Libft
DIRLIB = ./libft/
FILELIB = libft.a
NAMELFT = $(addprefix $(DIRLIB), $(FILELIB))

MAKEFLAGS += --no-print-directory
RM = rm -f
NAME = minishell

PARSING_SRC = srcs/parsing/token/id_token.c \
			  srcs/parsing/token/tokenization.c \
			  srcs/parsing/dollar/pid.c \
			  srcs/parsing/dollar/dollar.c \
			  srcs/parsing/check.c \
			  srcs/parsing/path.c \
			  srcs/parsing/parsing.c

BUILTIN_SRC = srcs/cmd/env/env.c \
			  srcs/cmd/env/create_env.c \

UTILS_SRC = srcs/utils/utils.c \
			srcs/utils/free.c \
			srcs/utils/for_list.c \
			srcs/utils/utils_token.c \
			srcs/error/msg.c \

MINISHELL_SRC = main.c $(PARSING_SRC) $(UTILS_SRC) $(BUILTIN_SRC)

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

re: fclean all

.PHONY: all clean fclean re
