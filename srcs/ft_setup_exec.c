/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:10:34 by tkleynts          #+#    #+#             */
/*   Updated: 2021/02/17 22:53:14 by igor             ###   ########.fr       */
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

t_rdir	ft_pipe_rd(t_rdir rdir, int filedes[2], int fd_def)
{
	if (fd_def == 1)
	{
		rdir.fdin = filedes[1];
		rdir.sdin = dup(1);
		dup2(rdir.fdin, 1);
	}
	else if (fd_def == 0)
	{
		rdir.fdout = filedes[0];
		rdir.sdout = dup(0);
		dup2(rdir.fdout, 0);
	}
	return (rdir);
}

t_rdir	ft_rdir_init(void)
{
	t_rdir	rdir;

	rdir.fdin = -2;
	rdir.fdout = -2;
	rdir.sdin = -1;
	rdir.sdout = -1;
	return (rdir);
}

int		ft_setup_exec(t_cmd *cmd, char ***envp, int *status)
{
	int		childpid;
	int		ret;
	int		index_pipe;
	int		filedes[2];
	t_rdir	file_rd;
	t_rdir	pipe_rd;

	pipe_rd = ft_rdir_init();
	while ((index_pipe = check_if_pipe(cmd)) > -1)
	{
		pipe(filedes);
		if ((childpid = fork()) == -1)
		{
			perror("fork");
			exit(1);
		}
		if (childpid == 0)
		{
			close(filedes[0]);
			file_rd = ft_rdir_init();
			file_rd = ft_file_rd(cmd, file_rd);
			pipe_rd = ft_pipe_rd(pipe_rd, filedes, 1);
			remove_after_pipe(cmd, index_pipe);
			ret = ft_sorter(cmd, envp);
			ft_close_all(file_rd);
			ft_close_all(pipe_rd);
            exit(0);
        }
        else
        {
			close(filedes[1]);
			remove_befor_pipe(cmd, index_pipe);
			ft_close_all(pipe_rd);
			pipe_rd = ft_pipe_rd(pipe_rd, filedes, 0);
		}
	}
	file_rd = ft_rdir_init();
	file_rd = ft_file_rd(cmd, file_rd);
	if (file_rd.fdin == -1 || file_rd.fdout == -1)
		return (-1);
	if (file_rd.fdin == -3 || file_rd.fdout == -3)
		return (1);
	if (file_rd.fdin == 0 || file_rd.fdout == 0)
		return (0);
	ret = ft_sorter(cmd, envp);
	waitpid(ret, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	ft_close_all(file_rd);
	ft_close_all(pipe_rd);
	return (ret);
}
