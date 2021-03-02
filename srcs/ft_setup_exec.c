/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:10:34 by tkleynts          #+#    #+#             */
/*   Updated: 2021/03/02 14:07:34 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_rdir_init(t_rdir *rdir)
{
	rdir->fdin = -2;
	rdir->fdout = -2;
	rdir->sdin = -1;
	rdir->sdout = -1;
}

/*
**	a[0] = filedes
**	a[1] = filedes
**	a[2] = childpid
**	a[3] = index_pipe
**	a[4] = ret
**
**	rd[0] = file_rd
**	rd[1] = pipe_rd
*/

void	ft_setup_exec_2(int a[5], t_rdir rd[2], t_cmd *cmd, char ***envp)
{
	if (a[2] == 0)
	{
		close(a[0]);
		ft_rdir_init(&rd[0]);
		ft_pipe_rd(&rd[1], a, 1);
		ft_file_rd(cmd, &rd[0]);
		remove_after_pipe(cmd, a[3]);
		ft_sorter(cmd, rd[1], envp, &a[4]);
		ft_close_all(rd[0]);
		ft_close_all(rd[1]);
		exit(0);
	}
	else
	{
		close(a[1]);
		remove_befor_pipe(cmd, a[3]);
		ft_close_all(rd[1]);
		ft_pipe_rd(&rd[1], a, 0);
	}
}

int		ft_setup_exec_3(t_rdir rd[2], t_cmd *cmd, int *status)
{
	ft_rdir_init(&rd[0]);
	ft_file_rd(cmd, &rd[0]);
	if (rd[0].fdout == 1)
		*status = 1;
	if (rd[0].fdin == -1 || rd[0].fdout == -1)
		return (-1);
	if (rd[0].fdin == -3 || rd[0].fdout == -3 || rd[0].fdout == 1)
		return (0);
	return (1);
}

int		ft_setup_exec(t_cmd *cmd, char ***envp, int *status)
{
	int		a[5];
	t_rdir	rd[2];

	ft_rdir_init(&rd[1]);
	while ((a[3] = check_if_pipe(cmd)) > -1)
	{
		pipe(a);
		if ((a[2] = fork()) == -1)
			exit(-1);
		ft_setup_exec_2(a, rd, cmd, envp);
	}
	if ((a[4] = ft_setup_exec_3(rd, cmd, status)) != 1)
		return (a[4]);
	ft_sorter(cmd, rd[1], envp, &a[4]);
	*status = a[4];
	waitpid(a[4], status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	ft_close_all(rd[0]);
	ft_close_all(rd[1]);
	if (*status == -1)
		return (-1);
	if (*status == -2)
		return ((*status = 1));
	return (0);
}
