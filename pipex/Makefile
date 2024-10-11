CC = 			cc
CFLAGS = 		-Wall -Wextra -Werror -g
RM = 			rm -f
NAME = 			Pipex
PIPEX_SRC = main.c

all :		$(NAME)

$(NAME) :
				@echo -e '\033[33;32mCreating Pipex... 🕗\n'
				@${CC}  ${PIPEX_SRC} ${CFLAGS} -o ${NAME}
				@echo -e '\033[33;32mPipex created ! 🎉'

re :
				@$(RM) $(NAME)
				@echo -e '\033[0;31mPipex deleted ! 🛑\n'
				@echo -e '\033[33;32mCreating Pipex... 🕗\n'
				@${CC} ${PIPEX_SRC} ${CFLAGS} -o ${NAME}
				@echo -e '\033[33;32mPipex created ! 🎉'

clean:
				@$(RM) $(NAME)
				@echo -e '\033[0;31mPipex deleted ! 🛑'

fclean:
				$(RM) $(NAME)
				@echo -e '\033[0;31mPipex deleted ! 🛑'

.PHONY: 	fclean clean re all