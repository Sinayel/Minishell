CC = 			cc

CFLAGS = -Wall -Wextra -Werror -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline -g

MAKEFLAGS += --no-print-directory
RM = 			rm -f

NAME = 			Minishell

#3 --------------------------- PARSING --------------------------- #
PARSING_SRC = srcs/parsing/verif.c \
			  srcs/parsing/dollar_check.c \
			  srcs/parsing/parsing.c

#1 ----------------------------- CMD ----------------------------- #
CMD_SRC = srcs/cmd/echo/echo.c \
		  srcs/cmd/echo/echo_check_dollar.c \
		  srcs/cmd/env/env.c

#! ---------------------------- ERROR ---------------------------- #
ERROR_SRC = srcs/error/dollar_error.c \
			srcs/error/args_error.c

#4 ---------------------------- UTILS ---------------------------- #
UTILS_SRC = srcs/utils/utils_2.c \
			srcs/utils/utils.c


MINISHELL_SRC = main.c $(PARSING_SRC) $(CMD_SRC) $(ERROR_SRC) $(UTILS_SRC)


ASCII_LOGO = -e "\
	███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
	████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
	██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
	██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"

all:		$(NAME)

$(NAME):	
				@echo -e '\033[35mCreating Minishell... 🕗\n'
				@echo $(ASCII_LOGO)
				@${CC} ${MINISHELL_SRC} ${CFLAGS} ${LDFLAGS} -o ${NAME}
				@echo -e '\033[33;32mMinishell created ! 🎉\033[0m'

re: 			
				@$(RM) $(NAME)
				@echo -e '\033[0;31mMinishell deleted ! 🛑'
				$(MAKE) all

clean:
				@$(RM) $(NAME)
				@echo -e '\033[0;31mMinishell deleted ! 🛑'

fclean: clean

.PHONY: 	fclean clean re all
