/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:05:55 by igor              #+#    #+#             */
/*   Updated: 2021/03/02 14:36:39 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_if_pipe(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (i <= cmd->argc)
	{
		if (!strncmp(cmd->argv[i], "|", 2))
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
	if (!(lst = malloc(sizeof(char *) * (index_pipe + 1))))
		return (0);
	while (i <= index_pipe)
	{
		lst[i] = cmd->argv[i];
		i++;
	}
	while (i <= cmd->argc)
	{
		free(cmd->argv[i]);
		i++;
	}
	cmd->argc = index_pipe - 1;
	free(cmd->argv);
	cmd->argv = lst;
	return (1);
}

int		remove_befor_pipe(t_cmd *cmd, int index_pipe)
{
	char	**lst;
	int		i;

	i = 0;
	if (!(lst = malloc(sizeof(char *) * (cmd->argc - index_pipe))))
		return (0);
	while (i <= cmd->argc - index_pipe - 1)
	{
		lst[i] = cmd->argv[index_pipe + i + 1];
		i++;
	}
	i = 0;
	while (i <= index_pipe)
	{
		free(cmd->argv[i]);
		i++;
	}
	free(cmd->argv);
	cmd->argv = lst;
	cmd->argc = cmd->argc - index_pipe - 1;
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