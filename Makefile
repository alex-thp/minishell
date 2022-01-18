NAME = minishell

#COMPILE

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

#LIBFT

LIBFT = libft/libft.a

#DIRECTORY

DIR_BUILD = build/
INC = -I libft

SRCS = main.c manage_env.c builtins.c builtins2.c create_tree.c utils_tree.c \
	   lexer.c files.c interpret.c is_execve.c signal.c signal_heredoc.c \
	   exit.c utils.c here_doc.c redir_list.c exec_tree.c\
	   parsing.c dollars.c redir.c more_utils.c more_utils2.c more_utils3.c

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
