CC = 			cc
CFLAGS = 		-Wall -Wextra -Werror -g
RM = 			rm -f
NAME = 			pipex
PIPEX_SRC = 	srcs/pipex_main.c srcs/pipex_utils.c srcs/pipex_utils2.c srcs/pipex_utils3.c srcs/ft_split.c srcs/gnl/get_next_line.c srcs/gnl/get_next_line_utils.c

all :		$(NAME)

$(NAME) :
				@echo -e '\033[33;32mCreating Pipex... 🕗\n'
				@${CC}  ${PIPEX_SRC} ${CFLAGS} -o ${NAME}
				@echo -e '\033[33;32mPipex created ! 🎉'

bonus :
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