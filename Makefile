CC = 			cc

CFLAGS = -Wall -Wextra -Werror -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline -g

RM = 			rm -f

NAME = 			Minishell

MINISHELL_SRC = 	main.c \
					srcs/parsing/verif.c \
					srcs/cmd/echo/echo.c \
					srcs/cmd/env/env.c \
					srcs/utils/utils_2.c \
					srcs/utils/utils.c \


all :		$(NAME)

$(NAME) :
				@echo -e '\033[33;32mCreating Minishell... 🕗\n'
				@${CC} ${MINISHELL_SRC} ${CFLAGS} ${LDFLAGS} -o ${NAME}
				@echo -e '\033[33;32mMinishell created ! 🎉'

re : 			
				@$(RM) $(NAME)
				@echo -e '\033[0;31mMinishell deleted ! 🛑\n'
				@echo -e '\033[33;32mCreating Minishell... 🕗\n'
				@${CC} ${MINISHELL_SRC} ${CFLAGS} ${LDFLAGS} -o ${NAME}
				@echo -e '\033[33;32mMinishell created ! 🎉'

clean:
				@$(RM) $(NAME)
				@echo -e '\033[0;31mMinishell deleted ! 🛑'

fclean:
				@$(RM) $(NAME)
				@echo -e '\033[0;31mMinishell deleted ! 🛑'

.PHONY: 	fclean clean re all