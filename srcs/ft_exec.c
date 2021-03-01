/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:22:53 by nlaurids          #+#    #+#             */
/*   Updated: 2021/02/17 18:27:55 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_sorter(t_cmd *cmd, t_rdir pipe_rd, char ***envp)
{
	int	ret;

	if (!ft_strncmp(cmd->name, "echo", 5))
		ret = ft_echo(cmd);
	else if (!ft_strncmp(cmd->name, "cd", 3))
		ret = ft_cd(cmd, pipe_rd, envp);
	else if (!ft_strncmp(cmd->name, "pwd", 4))
		ret = ft_pwd(cmd);
	else if (!ft_strncmp(cmd->name, "exit", 5))
		ret = ft_exit(cmd);
	else if (cmd->name[0] == '>')
		return (0);
	else if (!ft_strncmp(cmd->name, "env", 4))
		ret = ft_env(cmd, *envp);
	else if (!ft_strncmp(cmd->name, "unset", 6))
		ret = ft_unset(cmd, envp);
	else if (!ft_strncmp(cmd->name, "export", 7))
		ret = ft_export(cmd, envp);
	else
		ret = ft_exec(cmd, pipe_rd, *envp);
	return (ret);
}

int			set_argvlist(t_cmd *cmd, char ***argvlist)
{
	int		i;

	i = 1;
	if (!(*argvlist = ft_calloc(sizeof(char*), (cmd->arg_nbr + 2))))
		return (0);
	if (!((*argvlist)[0] = ft_strdup(cmd->name)))
		return (free_all(argvlist, 0));
	while (i <= cmd->arg_nbr && cmd->arg[i - 1][0] != '>'
			&& cmd->arg[i - 1][0] != '<')
	{
		if (!((*argvlist)[i] = ft_strdup(cmd->arg[i - 1])))
			return (free_all(argvlist, 0));
		i++;
	}
	(*argvlist)[i] = NULL;
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
		if (!((*pathlist)[i] = ft_memcat((*pathlist)[i], cmd->name,
				ft_strlen((*pathlist)[i]), ft_strlen(cmd->name))))
			return (free_all(pathlist, 0));
		i++;
	}
	return (1);
}

int			set_pathlist(t_cmd *cmd, char ***pathlist, char **envp)
{
	char	*path;
	int		emsg;

	emsg = 1;
	path = ft_getenv("PATH", envp);
	if (!path || !path[0])
		emsg = 2;
	if (!ft_hasslash(cmd->name) && path)
	{
		if (!ft_complet_pathlist(pathlist, path, cmd))
			return (0);
	}
	else
	{
		if (!(*pathlist = ft_calloc(sizeof(char *), 2)))
			return (0);
		if (!((*pathlist)[0] = ft_strdup(cmd->name)))
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
	char	**argvlist;
	pid_t	child_pid;

	if (!(set_argvlist(cmd, &argvlist)))
		return (-1);
	if (!(emsg = set_pathlist(cmd, &pathlist, envp)))
		return (free_all(&argvlist, -1));
	i = 0;
	if ((child_pid = fork()) == -1)
		return (free_all(&argvlist, free_all(&pathlist, -1)));
	if (child_pid == 0)
	{
		while (pathlist[i])
		{
			execve(pathlist[i], argvlist, envp);
			if (errno != ENOENT)
				exit(ft_errno_exec(cmd, pipe_rd, pathlist[i], emsg));
			i++;
		}
		exit(ft_errno_exec(cmd, pipe_rd, pathlist[i], emsg));
	}
	return (free_all(&argvlist, free_all(&pathlist, child_pid)));
}
