/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 14:48:29 by igor              #+#    #+#             */
/*   Updated: 2021/02/19 12:47:23 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_rdir	ft_open_all(t_rdir rdir)
{
	if (rdir.fdin > 0)
	{
		rdir.sdin = dup(1);
		dup2(rdir.fdin, 1);
	}
	if (rdir.fdout > 0)
	{
		rdir.sdout = dup(0);
		dup2(rdir.fdout, 0);
	}
	return (rdir);
}

void	ft_close_all(t_rdir rdir)
{
	if (rdir.fdin > 0)
	{
		close(rdir.fdin);
		dup2(rdir.sdin, 1);
		close(rdir.sdin);
	}
	if (rdir.fdout > 0)
	{
		close(rdir.fdout);
		dup2(rdir.sdout, 0);
		close(rdir.sdout);
	}
}

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

int		ft_redir_check(t_cmd *cmd)
{
	int fd;
	int i;

	i = 0;
	fd = -2;
	while (cmd->name[0] == '>')
	{
		if (cmd->name[1] == '>')
		{
			if ((fd = open(cmd->arg[0], O_WRONLY | O_CREAT | O_APPEND, S_IRWXU)) == -1)
				return (exit_write("File creation failed\n", 0, -1));
		}
		else if ((fd = open(cmd->arg[0], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
			return (exit_write("File creation failed\n", 0, -1));
		if (cmd->arg_nbr < 2)
			return (-3);
		if (remove_after_red(cmd, 0) == 0)
			return (0);
	}
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

int		ft_file_recup(t_cmd *cmd)
{
	int fd;
	int i;

	i = -1;
	fd = -2;
	while (cmd->name[0] == '<')
	{
		if ((fd = open(cmd->arg[0], O_RDONLY)) == -1)
			ft_errno(cmd);
		if (cmd->arg_nbr < 2)
			return (-1);
		if (remove_after_red(cmd, 0) == 0)
			return (0);
	}
	while (++i < cmd->arg_nbr)
		if (cmd->arg[i][0] == '<' && cmd->arg[i][0] != '|')
		{
			if (fd > 0)
				close(fd);
			if ((fd = open(cmd->arg[i + 1], O_RDONLY)) == -1)
				ft_errno(cmd);
		}
	return (fd);
}

t_rdir	ft_file_rd(t_cmd *cmd, t_rdir rdir)
{
	if ((cmd->name[0] == '>' || cmd->name[0] == '<') && cmd->arg_nbr == 0)
	{
		rdir.fdin = -1;
		write(2, "parse error near `\\n'\n", 22);
		return (rdir);
	}
	if (cmd->arg_nbr == 0)
		return (rdir);
	if (cmd->arg[cmd->arg_nbr - 1][0] == '>' || cmd->arg[cmd->arg_nbr - 1][0] == '<')
	{
		rdir.fdin = -1;
		write(2, "zsh: parse error near `\\n'\n", 27);
		return (rdir);
	}
	rdir.fdin = ft_redir_check(cmd);
	rdir.fdout = ft_file_recup(cmd);
	return (ft_open_all(rdir));
}
