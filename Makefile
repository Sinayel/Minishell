CC = 			cc

CFLAGS = -Wall -Wextra -Werror -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline

RM = 			rm -f

NAME = 			Minishell

MINISHELL_SRC = 	main.c \
					srcs/parsing/parsing_echo.c \
					srcs/utils/utils.c \


all :		$(NAME)

$(NAME) :
				@echo 'Creating Minishell... 🕗\n'
				@${CC} ${MINISHELL_SRC} ${CFLAGS} ${LDFLAGS} -o ${NAME}
				@echo 'Minishell created ! 🎉'

re : 			
				@$(RM) $(NAME)
				@echo 'Minishell deleted ! 🛑\n'
				@echo 'Creating Minishell... 🕗\n'
				@${CC} ${MINISHELL_SRC} ${CFLAGS} ${LDFLAGS} -o ${NAME}
				@echo 'Minishell created ! 🎉'

clean:
				@$(RM) $(NAME)
				@echo 'Minishell deleted ! 🛑'

fclean:
				$(RM) $(NAME)
				@echo 'Minishell deleted ! 🛑'

.PHONY: 	fclean clean re all
