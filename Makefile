# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/29 15:45:15 by ijacquet          #+#    #+#              #
#    Updated: 2021/03/02 14:37:22 by tkleynts         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
		
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
LIBFT		=	libft/libft.a

SRCS_NAME	=	main.c	\
				ft_cd.c \
				ft_echo.c \
				ft_env.c \
				ft_env_utils.c \
				ft_errno.c \
				ft_exec.c \
				ft_exit.c \
				ft_export.c \
				ft_display.c \
				ft_file_creator.c \
				ft_file_redirect.c \
				ft_lstcmd_utils.c \
				ft_lstline_utils.c \
				ft_parse_cmd.c \
				ft_parse_env.c \
				ft_parse_msg.c \
				ft_pipe_redir.c \
				ft_pwd.c \
				ft_reading.c \
				ft_setup_exec.c \
				ft_sig_handle.c \
				ft_unset.c \
				ft_utils.c \
				
INC_NAME	= 	minishell.h \
				structs.h \

SRCS		=	$(addprefix srcs/, $(SRCS_NAME))

INC			= $(addprefix includes/, $(INC_NAME))

OBJS		= 	$(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(INC)
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
