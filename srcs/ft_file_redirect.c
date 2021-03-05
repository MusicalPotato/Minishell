/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:19:17 by igor              #+#    #+#             */
/*   Updated: 2021/03/05 16:52:31 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_file_recup(t_cmd *cmd)
{
	int fd;
	int i;

	i = 0;
	fd = -2;
	while (cmd->argv[0][0] == '<')
	{
		if ((fd = open(cmd->argv[1], O_RDONLY)) == -1)
			return (ft_errno2(cmd));
		if (cmd->argc < 2)
			return (-3);
		if (remove_after_red(cmd, 1) == 0)
			return (0);
	}
	while (++i <= cmd->argc)
		if (cmd->argv[i][0] == '<' && cmd->argv[i][0] != '|')
		{
			if (fd > 0)
				close(fd);
			if ((fd = open(cmd->argv[i + 1], O_RDONLY)) == -1)
				return (ft_errno2(cmd));
		}
	return (fd);
}

t_rdir	*ft_open_all(t_rdir *rdir)
{
	if (rdir->fdin > 0)
	{
		rdir->sdin = dup(1);
		dup2(rdir->fdin, 1);
	}
	if (rdir->fdout > 0)
	{
		rdir->sdout = dup(0);
		dup2(rdir->fdout, 0);
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
