# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igor <igor@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/29 15:45:15 by ijacquet          #+#    #+#              #
#    Updated: 2020/11/24 11:19:27 by igor             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	Minishell
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address
LIBFT		=	libft/libft.a

SRCS_NAME	=	main.c	\
				ft_cd.c \
				ft_echo.c \
				ft_env.c \
				ft_env_utils.c \
				ft_exec.c \
				ft_exit.c \
				ft_export.c \
				ft_file_creator.c \
				ft_lstcmd_utils.c \
				ft_lstline_utils.c \
				ft_parse_info.c \
				ft_parse_env.c \
				ft_pwd.c \
				ft_reading.c \
				ft_sorter.c \
				ft_unset.c \
				ft_utils.c \

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
