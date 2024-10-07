CC = 			cc
CFLAGS = 		-Wall -Wextra -Werror -lreadline -g
RM = 			rm -f
NAME = 			Minishell
MINISHELL_SRC = pwd.c utils.c main.c

all :		$(NAME)

$(NAME) :
				@echo -e '\033[33;32mCreating Minishell... 🕗\n'
				@${CC}  ${MINISHELL_SRC} ${CFLAGS} -o ${NAME}
				@echo -e '\033[33;32mMinishell created ! 🎉'

re :
				@$(RM) $(NAME)
				@echo -e '\033[0;31mMinishell deleted ! 🛑\n'
				@echo -e '\033[33;32mCreating Minishell... 🕗\n'
				@${CC} ${MINISHELL_SRC} ${CFLAGS} -o ${NAME}
				@echo -e '\033[33;32mMinishell created ! 🎉'

clean:
				@$(RM) $(NAME)
				@echo -e '\033[0;31mMinishell deleted ! 🛑'

fclean:
				$(RM) $(NAME)
				@echo -e '\033[0;31mMinishell deleted ! 🛑'

.PHONY: 	fclean clean re all