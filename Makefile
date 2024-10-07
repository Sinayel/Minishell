CC = 			cc
CFLAGS = 		-Wall -Wextra -Werror -lreadline -g

RM = 			rm -f

NAME = 			so_long

SO_LONG_SRC = 	


all :		$(NAME)

$(NAME) :
				@echo -e '\033[33;32mCreating Minishell... 🕗\n'
				@${CC} ${SO_LONG_SRC} ${CFLAGS} -o ${NAME}
				@echo -e '\033[33;32mMinishell created ! 🎉'

re : 			
				@$(RM) $(NAME)
				@echo -e '\033[0;31mMinishell deleted ! 🛑\n'
				@echo -e '\033[33;32mCreating Minishell... 🕗\n'
				@${CC} ${SO_LONG_SRC} ${CFLAGS} -o ${NAME}
				@echo -e '\033[33;32mMinishell created ! 🎉'

clean:
				@$(RM) $(NAME)
				@echo -e '\033[0;31mMinishell deleted ! 🛑'

fclean:
				$(RM) $(NAME)
				@echo -e '\033[0;31mMinishell deleted ! 🛑'

.PHONY: 	fclean clean re all