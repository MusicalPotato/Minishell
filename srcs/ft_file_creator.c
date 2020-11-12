/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 14:48:29 by igor              #+#    #+#             */
/*   Updated: 2020/11/12 16:21:34 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     ft_file_create(t_cmd *cmd)
{
	int fd;
	char *line;

	line = malloc(1);
	if (cmd->name[1])
	{
		if ((fd = open(cmd->name + 1, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
			return (exit_write("File creation failed", 0, 0));
		if (cmd->arg_nbr)
			return (exit_write("command not found: ", cmd->arg[0], -1));
	}
	else if (cmd->arg_nbr == 0)
		return (exit_write("parse error near '\\n'\n", 0, -1));
	else
	{
		if ((fd = open(cmd->arg[0], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
			return (exit_write("File creation failed", 0, 0));
		if (cmd->arg_nbr > 1)
			return (exit_write("command not found: ", cmd->arg[1], -1));
	}
//	while (not ctrl+c)
//	{
	get_next_line(1, &line);
	write(fd, line, ft_strlen(line));
//	}
	close(fd);
	return (1);
}