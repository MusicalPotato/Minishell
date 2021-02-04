/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_creator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 14:48:29 by igor              #+#    #+#             */
/*   Updated: 2021/02/04 14:09:51 by tkleynts         ###   ########.fr       */
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

int		ft_redir_check(t_cmd *cmd)
{
	int fd;
	int i;

	i = 0;
	fd = -2;
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
	while (++i < cmd->arg_nbr)
		if (cmd->arg[i][0] == '<' && cmd->arg[i][0] != '|')
		{
			if (fd > 0)
				close(fd);
			if ((fd = open(cmd->arg[i + 1], O_RDONLY)) == -1)
			{
				write(2, cmd->arg[i + 1], ft_strlen(cmd->arg[i + 1]));
				return (exit_write(" : No such file or directory\n", 0, -1));
			}
		}
	return (fd);
}

int		ft_file_create(t_cmd *cmd)
{
	int fd;
	int i;

	i = 0;
	if (cmd->arg_nbr == 0)
		return (exit_write("syntax error near unexpected token `newline'\n", 0, -1));
	if (cmd->name[1] == '>')
	{
		if ((fd = open(cmd->arg[0], O_WRONLY | O_CREAT | O_APPEND, S_IRWXU)) == -1)
			return (exit_write("File creation failed\n", 0, -1));
	}
	else if ((fd = open(cmd->arg[0], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) == -1)
		return (exit_write("File creation failed\n", 0, -1));
	if (cmd->arg[cmd->arg_nbr - 1][0] == '>')
		return (exit_write("syntax error near unexpected token `newline'\n", 0, -1));
	while (++i < cmd->arg_nbr && cmd->arg[i][0] != '|')
	{
		close(fd);
		if (cmd->arg[i][0] == '>' && cmd->arg[i][1] == '>')
		{
			if ((fd = open(cmd->arg[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1)
				return (exit_write("File creation failed\n", 0, -1));
		}
		else if (cmd->arg[i][0] == '>')
			if ((fd = open(cmd->arg[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
				return (exit_write("File creation failed\n", 0, -1));
	}
	i = 0;
	while (++i < cmd->arg_nbr)
		if (cmd->arg[i - 1][0] != '>' && cmd->arg[i - 1][0] != '<' && cmd->arg[i][0] != '>' && cmd->arg[i][0] != '<')
			return (exit_write("command not found : ", cmd->arg[i], -1));
	close(fd);
	return (1);
}

t_rdir	ft_file_rd(t_cmd *cmd, t_rdir rdir)
{
	if (cmd->arg_nbr == 0)
		return (rdir);
	if (cmd->arg[cmd->arg_nbr - 1][0] == '>' || cmd->arg[cmd->arg_nbr - 1][0] == '<')
	{
		rdir.fdin = -1;
		write(2, "syntax error near unexpected token `newline'\n", 45);
		return (rdir);
	}
	rdir.fdin = ft_redir_check(cmd);
	rdir.fdout = ft_file_recup(cmd);
	return (ft_open_all(rdir));
}
