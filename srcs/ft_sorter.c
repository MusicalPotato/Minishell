/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 14:48:42 by igor              #+#    #+#             */
/*   Updated: 2021/01/25 16:20:01 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_cmd_path_cmp(t_cmd *cmd, char **envp)
{
	int		i;
	char	**pathlist;
	char	**argvlist;
	int		status;

	i = 1;
	argvlist = malloc(sizeof(char*) * (cmd->arg_nbr + 2));
	argvlist[0] = ft_strdup(cmd->name);
	while (i <= cmd->arg_nbr && cmd->arg[i - 1][0] != '>' && cmd->arg[i - 1][0] != '<')
	{
		argvlist[i] = ft_strdup(cmd->arg[i - 1]);
		i++;
	}
	argvlist[i] = NULL;
	i = 0;
	pathlist = ft_split(ft_getenv("PATH", envp), ':');
	while (pathlist[i])
	{
		if (!(pathlist[i] = ft_memcat(pathlist[i], "/", ft_strlen(pathlist[i]), 1))
				|| !(pathlist[i] = ft_memcat(pathlist[i], cmd->name, ft_strlen(pathlist[i]), ft_strlen(cmd->name))))
			return (free_all(&argvlist, free_all(&pathlist, 0)));
		i++;
	}
	i = 0;
	if (fork() == -1)
		return (free_all(&argvlist, free_all(&pathlist, 0)));
	if (wait(&status) < 0)
	{
		while (pathlist[i])
		{
			execve(pathlist[i], argvlist, envp);
			if (errno != ENOENT)
				return (0);
			i++;
		}
		ft_printf("%s: command not found\n", cmd->name);
		return (0);
	}
	return (free_all(&argvlist, free_all(&pathlist, 1)));
}

t_rdir	ft_rdir_init()
{
	t_rdir	rdir;
	
	rdir.fdin = -2;
	rdir.fdout = -2;
	rdir.sdin = -1;
	rdir.sdout = -1;
	return (rdir);
}

int		ft_cmd_cmp(t_cmd *cmd, char ***envp)
{
	t_rdir	rdir;

	int		ret;

	rdir = ft_rdir_init();
	rdir = ft_file_redirect(cmd, rdir);
	// appelez ft_rdir_pipe
	if (rdir.fdin == 0 || rdir.fdin == -1 || rdir.fdout == 0 || rdir.fdout == -1)
		return (rdir.fdin);
	if (!ft_strncmp(cmd->name, "echo", 5))
		ret = ft_echo(cmd);
	else if (!ft_strncmp(cmd->name, "cd", 3))
		ret = ft_cd(cmd, *envp);
	else if (!ft_strncmp(cmd->name, "pwd", 4))
		ret = ft_pwd(cmd);
	else if (!ft_strncmp(cmd->name, "exit", 5))
		ret = ft_exit(cmd);
	else if (cmd->name[0] == '.' && cmd->name[1] == '/')
		ret = ft_exec(cmd, *envp);
	else if (cmd->name[0] == '>')
		ret = ft_file_create(cmd);
	else if (!ft_strncmp(cmd->name, "env", 4))
		ret = ft_env(cmd, *envp);
	else if (!ft_strncmp(cmd->name, "unset", 6))
		ret = ft_unset(cmd, envp);
	else if (!ft_strncmp(cmd->name, "export", 7))
		ret = ft_export(cmd, envp);
	else
		ret = ft_cmd_path_cmp(cmd, *envp);
	ft_close_all(rdir);
	//retablire fd pipe
	return (ret);
}
