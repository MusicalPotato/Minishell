/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:10:34 by tkleynts          #+#    #+#             */
/*   Updated: 2021/03/02 14:37:06 by tkleynts         ###   ########.fr       */
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
**	v[0] = filedes
**	v[1] = filedes
**	v[2] = childpid
**	v[3] = index_pipe
**	v[4] = ret
**
**	rd[0] = file_rd
**	rd[1] = pipe_rd
*/

static void	ft_setup_exec_pipe(t_data *d, t_cmd *cmd, int v[5], t_rdir rd[2])
{
	if (v[2] == 0)
	{
		close(v[0]);
		ft_rdir_init(&rd[0]);
		ft_pipe_rd(&rd[1], v, 1);
		ft_file_rd(cmd, &rd[0]);
		remove_after_pipe(cmd, v[3]);
		ft_sorter(d, cmd, rd[1], &v[4]);
		ft_close_all(rd[0]);
		ft_close_all(rd[1]);
		exit(0);
	}
	else
	{
		close(v[1]);
		remove_befor_pipe(cmd, v[3]);
		ft_close_all(rd[1]);
		ft_pipe_rd(&rd[1], v, 0);
	}
}

static int	ft_setup_exec_3(t_rdir rd[2], t_cmd *cmd, int *status)
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

int			ft_setup_exec(t_data *d, t_cmd *cmd)
{
	int		v[5];
	t_rdir	rd[2];

	ft_rdir_init(&rd[1]);
	while ((v[3] = check_if_pipe(cmd)) > -1)
	{
		pipe(v);
		if ((v[2] = fork()) == -1)
			exit(-1);
		ft_setup_exec_pipe(d, cmd, v, rd);
	}
	if ((v[4] = ft_setup_exec_3(rd, cmd, &(d->status))) != 1)
		return (v[4]);
	ft_sorter(d, cmd, rd[1], &v[4]);
	d->status = v[4];
	waitpid(v[4], &(d->status), 0);
	if (WIFEXITED(d->status))
		d->status = WEXITSTATUS(d->status);
	ft_close_all(rd[0]);
	ft_close_all(rd[1]);
	if (d->status == -1)
		return (-1);
	if (d->status == -2)
		return ((d->status = 1));
	return (0);
}
