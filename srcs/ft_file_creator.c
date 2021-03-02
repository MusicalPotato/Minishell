/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 14:48:29 by igor              #+#    #+#             */
/*   Updated: 2021/03/01 18:00:57 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		remove_after_red(t_cmd *cmd, int index_red)
{
	char	**lst;
	int		i;

	i = 0;
	if (!(lst = malloc(sizeof(char *) * (cmd->arg_nbr - index_red - 1))))
		return (0);
	free(cmd->name);
	cmd->name = cmd->arg[index_red + i + 1];
	while (i < cmd->arg_nbr - index_red - 2)
	{
		lst[i] = cmd->arg[index_red + i + 2];
		i++;
	}
	i = 0;
	while (i < index_red + 1)
	{
		free(cmd->arg[i]);
		i++;
	}
	free(cmd->arg);
	cmd->arg = lst;
	cmd->arg_nbr = cmd->arg_nbr - index_red - 2;
	return (1);
}

int		ft_redir_check_1(t_cmd *cmd, int fd)
{
	if (cmd->name[1] == '>')
	{
		if ((fd = open(cmd->arg[0], O_WRONLY | O_CREAT | O_APPEND,
												S_IRWXU)) == -1)
			return (exit_write("File creation failed\n", 0, -1));
	}
	else if ((fd = open(cmd->arg[0], O_WRONLY | O_CREAT | O_TRUNC,
												S_IRWXU)) == -1)
		return (exit_write("File creation failed\n", 0, -1));
	if (cmd->arg_nbr < 2)
		return (-3);
	if (remove_after_red(cmd, 0) == 0)
		return (-1);
	return (fd);
}

int		ft_redir_check(t_cmd *cmd, int fd)
{
	int i;

	i = 0;
	while (cmd->name[0] == '>')
		if ((fd = ft_redir_check_1(cmd, fd)) < 0)
			return (fd);
	while (i < cmd->arg_nbr)
	{
		if (cmd->arg[i][0] == '>')
		{
			if (fd > 0)
				close(fd);
			if (cmd->arg[i][1] == '>')
			{
				if ((fd = open(cmd->arg[i + 1], O_WRONLY | O_CREAT
													| O_APPEND, 0666)) == -1)
					return (exit_write("File creation failed\n", 0, -1));
			}
			else if ((fd = open(cmd->arg[i + 1], O_WRONLY | O_CREAT
													| O_TRUNC, 0666)) == -1)
				return (exit_write("File creation failed\n", 0, -1));
		}
		i++;
	}
	return (fd);
}

void	ft_file_rd(t_cmd *cmd, t_rdir *rdir)
{
	if (cmd->arg_nbr == 0)
		return ;
	rdir->fdin = ft_redir_check(cmd, -2);
	rdir->fdout = ft_file_recup(cmd);
	ft_open_all(*rdir);
	return ;
}
