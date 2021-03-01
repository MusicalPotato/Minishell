/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:19:17 by igor              #+#    #+#             */
/*   Updated: 2021/03/01 14:20:33 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_file_recup(t_cmd *cmd)
{
	int fd;
	int i;

	i = -1;
	fd = -2;
	while (cmd->name[0] == '<')
	{
		if ((fd = open(cmd->arg[0], O_RDONLY)) == -1)
			return (ft_errno2(cmd));
		if (cmd->arg_nbr < 2)
			return (-3);
		if (remove_after_red(cmd, 0) == 0)
			return (0);
	}
	while (++i < cmd->arg_nbr)
		if (cmd->arg[i][0] == '<' && cmd->arg[i][0] != '|')
		{
			if (fd > 0)
				close(fd);
			if ((fd = open(cmd->arg[i + 1], O_RDONLY)) == -1)
				return (ft_errno2(cmd));
		}
	return (fd);
}

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