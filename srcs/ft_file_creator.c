/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 14:48:29 by igor              #+#    #+#             */
/*   Updated: 2021/03/05 15:43:11 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		remove_after_red(t_cmd *cmd, int index_red)
{
	char	**lst;
	int		i;

	i = 0;
	if (!(lst = malloc(sizeof(char *) * (cmd->argc - index_red))))
		return (0);
	while (i <= cmd->argc - index_red - 1)
	{
		lst[i] = cmd->argv[index_red + i + 1];
		i++;
	}
	i = 0;
	while (i <= index_red)
	{
		free(cmd->argv[i]);
		i++;
	}
	free(cmd->argv);
	cmd->argv = lst;
	cmd->argc = cmd->argc - index_red - 1;
	return (1);
}

int		ft_redir_check_1(t_cmd *cmd, int fd)
{
	if (cmd->argv[0][1] == '>')
	{
		if ((fd = open(cmd->argv[1], O_WRONLY | O_CREAT | O_APPEND,
												S_IRWXU)) == -1)
			return (exit_write("File creation failed\n", 0, -1));
	}
	else if ((fd = open(cmd->argv[1], O_WRONLY | O_CREAT | O_TRUNC,
												S_IRWXU)) == -1)
		return (exit_write("File creation failed\n", 0, -1));
	if (cmd->argc < 2)
		return (-3);
	if (remove_after_red(cmd, 1) == 0)
		return (-1);
	return (fd);
}

int		ft_redir_check(t_cmd *cmd, int fd)
{
	int i;

	i = 1;
	while (cmd->argv[0][0] == '>')
		if ((fd = ft_redir_check_1(cmd, fd)) < 0)
			return (fd);
	while (i <= cmd->argc)
	{
		if (cmd->argv[i][0] == '>')
		{
			if (fd > 0)
				close(fd);
			if (cmd->argv[i][1] == '>')
			{
				if ((fd = open(cmd->argv[i + 1], O_WRONLY | O_CREAT
													| O_APPEND, 0666)) == -1)
					return (exit_write("File creation failed\n", 0, -1));
			}
			else if ((fd = open(cmd->argv[i + 1], O_WRONLY | O_CREAT
													| O_TRUNC, 0666)) == -1)
				return (exit_write("File creation failed\n", 0, -1));
		}
		i++;
	}
	return (fd);
}

void	ft_file_rd(t_cmd *cmd, t_rdir *rdir)
{
	if (cmd->argc == 0)
		return ;
	rdir->fdin = ft_redir_check(cmd, -2);
	rdir->fdout = ft_file_recup(cmd);
	ft_open_all(rdir);
	return ;
}
