# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adylewsk <adylewsk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 11:27:17 by adylewsk          #+#    #+#              #
#    Updated: 2021/11/24 11:18:14 by adylewsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

#COMPILE

CC = gcc
CFLAGS = -Wall -Wextra -Werror
BUFFER = 64

#DIRECTORY

DIR_LIB = libft/
DIR_MY_FT = my_ft/
DIR_GNL = gnl/
DIR_PRINTF = ft_printf/
DIR_BUILD = build/

#SOURCES

SRCS_LIB = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c		\
ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c ft_memchr.c	\
ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c			\
ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strcat.c		\
ft_strchr.c ft_strcpy.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c	\
ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c\
ft_substr.c ft_tolower.c ft_toupper.c

SRCS_GNL = get_next_line.c

SRCS_PRINTF = utils/ft_itoa.c	\
srcs/ft_check.c srcs/ft_convert_to.c srcs/ft_convert.c srcs/ft_param.c		\
print/ft_print_nbr.c print/ft_print_ptr.c print/ft_print_str.c				\
print/ft_print_champ.c ft_printf.c

SRCS_MY_FT = ft_intlen.c ft_max.c ft_min.c ft_pow.c ft_putchar.c ft_putstr.c\
ft_puttab.c ft_strisdigit.c ft_tabisdigit.c ft_tablen.c ft_splits.c			\
ft_freetab.c

SRCS = $(addprefix $(DIR_LIB), $(SRCS_LIB:.c=.o)) \
$(addprefix $(DIR_MY_FT), $(SRCS_MY_FT:.c=.o)) \
$(addprefix $(DIR_GNL), $(SRCS_GNL:.c=.o)) \
$(addprefix $(DIR_PRINTF), $(SRCS_PRINTF:.c=.o))

OBJS = $(addprefix $(DIR_BUILD), $(patsubst %.c,%.o,$(SRCS)))

all : $(NAME)

$(DIR_BUILD)% :
	mkdir -p $@

.SECONDEXPANSION:

$(NAME) :$(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJS): $(DIR_BUILD)%.o:%.c | $$(@D)/
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER) -c $< -o $@

clean :
	rm -rf $(DIR_BUILD)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
