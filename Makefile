# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/29 15:45:15 by ijacquet          #+#    #+#              #
#    Updated: 2020/10/29 15:55:27 by ijacquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	Minishell
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address
LIBFT		=	libft/libft.a

SRCS_NAME	=	main.c	\
				ft_reading.c

SRCS		=	$(addprefix srcs/, $(SRCS_NAME))

OBJS		= 	$(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
			$(CC)  $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT) : 
			make -C libft all

clean :
			rm -f $(OBJS)
			make -C libft clean

fclean :	clean
			rm -f $(NAME)
			make -C libft fclean

re: fclean all
