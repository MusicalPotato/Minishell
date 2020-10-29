# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gorban <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 16:07:26 by gorban            #+#    #+#              #
#    Updated: 2019/10/15 21:57:06 by gorban           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
		ft_memcmp.c ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
		ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
		ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_memcat.c ft_rev_int_tab.c \
		ft_sort.c ft_sqrt.c ft_swap.c ft_ultoa_base.c ft_intlen.c ft_freeturn.c \
		get_next_line.c ft_stradd_back.c

OBJS = $(SRC:.c=.o)

CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	make -C ft_printf
	cp ft_printf/libftprintf.a $(NAME)
	ar -rc $(NAME) $?

clean:
	rm -f $(OBJS)
	make -C ft_printf clean

fclean:	clean
	rm -f $(NAME)
	make -C ft_printf fclean

re: fclean all

.PHONY = all clean fclean re bonus
