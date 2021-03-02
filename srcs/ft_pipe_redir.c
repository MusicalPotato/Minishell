/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:05:55 by igor              #+#    #+#             */
/*   Updated: 2021/03/02 14:07:08 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_if_pipe(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->arg_nbr)
	{
		if (!strncmp(cmd->arg[i], "|", 2))
			return (i);
		i++;
	}
	return (-1);
}

int		remove_after_pipe(t_cmd *cmd, int index_pipe)
{
	char	**lst;
	int		i;

	i = 0;
	if (!(lst = malloc(sizeof(char *) * (index_pipe))))
		return (0);
	while (i < index_pipe)
	{
		lst[i] = cmd->arg[i];
		i++;
	}
	while (i < cmd->arg_nbr)
	{
		free(cmd->arg[i]);
		i++;
	}
	cmd->arg_nbr = index_pipe;
	free(cmd->arg);
	cmd->arg = lst;
	return (1);
}

int		remove_befor_pipe(t_cmd *cmd, int index_pipe)
{
	char	**lst;
	int		i;

	i = 0;
	if (!(lst = malloc(sizeof(char *) * (cmd->arg_nbr - index_pipe - 1))))
		return (0);
	free(cmd->name);
	cmd->name = cmd->arg[index_pipe + i + 1];
	while (i < cmd->arg_nbr - index_pipe - 2)
	{
		lst[i] = cmd->arg[index_pipe + i + 2];
		i++;
	}
	i = 0;
	while (i < index_pipe + 1)
	{
		free(cmd->arg[i]);
		i++;
	}
	free(cmd->arg);
	cmd->arg = lst;
	cmd->arg_nbr = cmd->arg_nbr - index_pipe - 2;
	return (1);
}

void	ft_pipe_rd(t_rdir *rdir, int filedes[2], int fd_def)
{
	if (fd_def == 1)
	{
		rdir->fdin = filedes[1];
		rdir->sdin = dup(1);
		dup2(rdir->fdin, 1);
	}
	else if (fd_def == 0)
	{
		rdir->fdout = filedes[0];
		rdir->sdout = dup(0);
		dup2(rdir->fdout, 0);
	}
}