NAME = minishell

#COMPILE

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

#LIBFT

LIBFT = libft/libft.a

#DIRECTORY

DIR_BUILD = build/
INC = -I libft

SRCS = main.c manage_env.c builtins.c create_tree.c utils_tree.c \
	   lexer.c files.c interpret.c signal.c exit.c\

OBJS = $(addprefix $(DIR_BUILD), $(SRCS:.c=.o))

all : $(LIBFT) $(DIR_BUILD) $(NAME)

$(DIR_BUILD):
	mkdir -p $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -L libft -lft -lreadline

$(LIBFT):
	make -C libft/


$(OBJS): $(DIR_BUILD)%.o: %.c
	$(CC) -c $(CFLAGS) $(INC) $< -o $@



lclean:
	make -C libft clean

lfclean:
	make -C libft fclean

lre:
	make -C libft re

mclean:
	rm -rf $(DIR_BUILD)

mfclean: mclean
	rm -rf $(NAME)

clean: lclean mclean

fclean: lfclean mfclean

re: lre mfclean all

.PHONY: all clean fclean re
