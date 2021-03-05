/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:22:53 by nlaurids          #+#    #+#             */
/*   Updated: 2021/03/01 18:04:17 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_sorter(t_data *d, t_cmd *cmd, t_rdir pipe_rd, int *ret)
{
	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		*ret = ft_echo(cmd);
	else if (!ft_strncmp(cmd->argv[0], "cd", 3))
		*ret = ft_cd(cmd, pipe_rd, &(d->envp));
	else if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		*ret = ft_pwd(cmd);
	else if (!ft_strncmp(cmd->argv[0], "exit", 5))
		*ret = ft_exit(cmd, 0);
	else if (cmd->argv[0][0] == '>')
		*ret = 0;
	else if (!ft_strncmp(cmd->argv[0], "env", 4))
		*ret = ft_env(cmd, d->envp);
	else if (!ft_strncmp(cmd->argv[0], "unset", 6))
		*ret = ft_unset(cmd, &(d->envp));
	else if (!ft_strncmp(cmd->argv[0], "export", 7))
		*ret = ft_export(cmd, &(d->envp));
	else
		*ret = ft_exec(cmd, pipe_rd, d->envp);
}

static int	ft_set_argvlist(t_cmd *cmd)
{
	int		i;
	char	**argvlist;

	i = 0;
	while (i <= cmd->argc && cmd->argv[i][0] != '>'
			&& cmd->argv[i][0] != '<')
		i++;
	if (!(argvlist = ft_calloc(sizeof(char *), (i + 1))))
		return (0);
	i = 0;
	while (i <= cmd->argc && cmd->argv[i][0] != '>'
			&& cmd->argv[i][0] != '<')
	{
		if (!(argvlist[i] = ft_strdup(cmd->argv[i])))
			return (free_all(&argvlist, 0));
		i++;
	}
	argvlist[i] = NULL;
	if (!(cmd->argv = ft_stradd_back(cmd->argv, NULL, cmd->argc)))
		return (free_all(&argvlist, -1));
	free_all(&(cmd->argv), 1);
	cmd->argv = argvlist;
	return (1);
}

static int	ft_complet_pathlist(char ***pathlist, char *path, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!(*pathlist = ft_split(path, ':')))
		return (0);
	while ((*pathlist)[i])
	{
		if ((*pathlist)[i][0])
			if (!((*pathlist)[i] = ft_memcat((*pathlist)[i], "/",
				ft_strlen((*pathlist)[i]), 1)))
				return (free_all(pathlist, 0));
		if (!((*pathlist)[i] = ft_memcat((*pathlist)[i], cmd->argv[0],
				ft_strlen((*pathlist)[i]), ft_strlen(cmd->argv[0]))))
			return (free_all(pathlist, 0));
		i++;
	}
	return (1);
}

int			ft_set_pathlist(t_cmd *cmd, char ***pathlist, char **envp)
{
	char	*path;
	int		emsg;

	emsg = 1;
	path = ft_getenv("PATH", envp);
	if (!path || !path[0])
		emsg = 2;
	if (!ft_hasslash(cmd->argv[0]) && path)
	{
		if (!ft_complet_pathlist(pathlist, path, cmd))
			return (0);
	}
	else
	{
		if (!(*pathlist = ft_calloc(sizeof(char *), 2)))
			return (0);
		if (!((*pathlist)[0] = ft_strdup(cmd->argv[0])))
			return (free_all(pathlist, 0));
		(*pathlist)[1] = NULL;
	}
	return (emsg);
}

int			ft_exec(t_cmd *cmd, t_rdir pipe_rd, char **envp)
{
	int		i;
	int		emsg;
	char	**pathlist;
	pid_t	child_pid;

	if (!ft_set_argvlist(cmd))
		return (-1);
	if (!(emsg = ft_set_pathlist(cmd, &pathlist, envp)))
		return (-1);
	i = 0;
	if ((child_pid = fork()) == -1)
		return (free_all(&pathlist, -1));
	if (child_pid == 0)
	{
		while (pathlist[i])
		{
			execve(pathlist[i], cmd->argv, envp);
			if (errno != ENOENT)
				exit(ft_errno_exec(cmd, pipe_rd, pathlist[i], emsg));
			i++;
		}
		exit(ft_errno_exec(cmd, pipe_rd, pathlist[i], emsg));
	}
	return (free_all(&pathlist, child_pid));
}
