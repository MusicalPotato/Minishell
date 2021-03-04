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
				builtin/ft_cd.c \
				builtin/ft_echo.c \
				builtin/ft_exit.c \
				builtin/ft_export.c \
				builtin/ft_pwd.c \
				builtin/ft_unset.c \
				ft_env.c \
				ft_env_utils.c \
				ft_errno.c \
				ft_exec.c \
				ft_display.c \
				ft_file_creator.c \
				ft_file_redirect.c \
				ft_parse_cmd.c \
				ft_parse_env.c \
				ft_parse_msg.c \
				ft_pipe_redir.c \
				ft_reading.c \
				ft_setup_exec.c \
				ft_sig_handle.c \
				ft_utils.c \
				struct/ft_lstcmd_utils.c \
				struct/ft_lstdata_utils.c \
				struct/ft_lsthist_utils.c \
				
INC_NAME	= 	minishell.h \
				structs.h \

SRCS		=	$(addprefix srcs/, $(SRCS_NAME))

INC			=	$(addprefix includes/, $(INC_NAME))

OBJS		= 	$(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT) $(INC)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lncurses

$(LIBFT) : 
			make -C libft all

clean :
			rm -f $(OBJS)
			make -C libft clean

fclean :	clean
			rm -f $(NAME)
			rm -f history
			make -C libft fclean

re: fclean all
