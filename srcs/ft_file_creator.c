/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 14:48:29 by igor              #+#    #+#             */
/*   Updated: 2020/11/20 03:35:40 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     ft_file_create(t_cmd *cmd)
{
	int fd;
	int i;

	i = 1;
	if (cmd->name[1] == '<' || (cmd->name[1] == '>' && cmd->name[2] == '<'))
		return (exit_write("syntax error near unexpected token `<'\n", 0, -1));
	else if (cmd->name[1] && cmd->name[1] == '>')
	{
		if (cmd->name[2] && cmd->name[2] != '>')
		{
			if ((fd = open(cmd->name + 2, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU)) == -1)
				return (exit_write("File creation failed", 0, 0));
			if (cmd->arg_nbr)
				return (exit_write("command not found: ", cmd->arg[0], -1));
		}
		else if (cmd->name[2] == '>')
			return (exit_write("syntax error near unexpected token `>'\n", 0, -1));
		else
		{
			if ((fd = open(cmd->arg[0], O_WRONLY | O_CREAT | O_APPEND, S_IRWXU)) == -1)
				return (exit_write("File creation failed", 0, 0));
			if (cmd->arg_nbr > 1)
				return (exit_write("command not found: ", cmd->arg[1], -1));
		}	
	}
	else if (cmd->name[1])
	{
		if ((fd = open(cmd->name + 1, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
			return (exit_write("File creation failed", 0, 0));
		if (cmd->arg_nbr)
			return (exit_write("command not found: ", cmd->arg[0], -1));
	}
	else if (cmd->arg_nbr == 0)
		return (exit_write("syntax error near unexpected token `newline'\n", 0, -1));
	else
	{
		if ((fd = open(cmd->arg[0], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
			return (exit_write("File creation failed", 0, 0));
		if (cmd->arg_nbr > 1)
			return (exit_write("command not found: ", cmd->arg[1], -1));
	}
	close(fd);
	return (1);
}

int     ft_file_redirect(t_cmd *cmd, char *msg)
{
	int fd;
	int i;
	char *line;

	i = 0;
	line = malloc(1);
	while (cmd->arg[i][0] != '>')
		i++;
	i++;
	if (cmd->arg[i - 1][1])
	{
		printf("here\n");
		if ((fd = open(cmd->arg[i], O_WRONLY | O_CREAT | O_APPEND, S_IRWXU)) == -1)
			return (exit_write("File creation failed", 0, 0));
		printf("here\n");
	}
	else if (cmd->arg_nbr == i)
		return (exit_write("syntax error near unexpected token `newline'\n", 0, -1));
	else
	{
		if ((fd = open(cmd->arg[i], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
			return (exit_write("File creation failed", 0, 0));
	}
	write(fd, msg, ft_strlen(msg));
	close(fd);
	return (1);
}