SRCS = main.c manage_env.c
CFLAGS = -Wall -Werror -Wextra
NAME = minishell
INC = minishell.h
OBJS = ${SRCS:%.c=%.o}

all: ${NAME}

${NAME} : ${OBJS} ${INC}
	gcc ${CFLAGS} ${OBJS} -lreadline -o minishell

%.c : %.o
	@gcc ${CFLAGS} -c -I minishell.h

extend_flag:
	$(eval CFLAGS+=-g)

clean:
	@rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all