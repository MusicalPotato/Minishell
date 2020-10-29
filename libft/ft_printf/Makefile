# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gorban <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/26 00:19:20 by gorban            #+#    #+#              #
#    Updated: 2019/11/26 00:48:53 by gorban           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = ft_printf.c parse.c parse_int.c parse_char.c parse_string.c parse_hex.c \
        parse_address.c ft_is.c ft_tools.c \

OBJS = $(SRC:.c=.o)

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar -rc $(NAME) $?

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re
