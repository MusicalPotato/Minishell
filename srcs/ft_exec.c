/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:22:53 by nlaurids          #+#    #+#             */
/*   Updated: 2021/01/12 16:29:36 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_sorter(t_cmd *cmd, char ***envp)
{
	int        ret;

    if (!ft_strncmp(cmd->name, "echo", 5))
        ret = ft_echo(cmd);
    else if (!ft_strncmp(cmd->name, "cd", 3))
        ret = ft_cd(cmd, *envp);
    else if (!ft_strncmp(cmd->name, "pwd", 4))
        ret = ft_pwd(cmd);
    else if (!ft_strncmp(cmd->name, "exit", 5))
        return (0);
    else if (cmd->name[0] == '>')
        ret = ft_file_create(cmd);
    else if (!ft_strncmp(cmd->name, "env", 4))
        ret = ft_env(cmd, *envp);
    else if (!ft_strncmp(cmd->name, "unset", 6))
        ret = ft_unset(cmd, envp);
    else if (!ft_strncmp(cmd->name, "export", 7))
        ret = ft_export(cmd, envp);
	else
		ret = ft_exec(cmd, *envp);
    return (ret);
}

int		ft_exec(t_cmd *cmd, char **envp)
{
	int		i;
	char	**pathlist;
	char	**argvlist;
	pid_t	child_pid;

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
	if (cmd->name[0] == '.' && cmd->name[1] == '/')
	{
		pathlist = malloc(sizeof(char*) * 2);
		pathlist[0] = ft_strdup(cmd->name);
		pathlist[1] = NULL;
	}
	else
	{
		pathlist = ft_split(ft_getenv("PATH", envp), ':');
		while (pathlist[i])
		{
			if (!(pathlist[i] = ft_memcat(pathlist[i], "/", ft_strlen(pathlist[i]), 1))
					|| !(pathlist[i] = ft_memcat(pathlist[i], cmd->name, ft_strlen(pathlist[i]), ft_strlen(cmd->name))))
				return (free_all(&argvlist, free_all(&pathlist, 0)));
			i++;
		}
		i = 0;
	}
	if ((child_pid = fork()) == -1)
		return (free_all(&argvlist, free_all(&pathlist, 0)));
	if (child_pid == 0)
	{
		while (pathlist[i]) //pathlist a 1 (i=0) element pour nos cmd sinon i=x element(s)
		{
			execve(pathlist[i], argvlist, envp);
			if (errno != ENOENT)
				return (0);
			i++;
		}
		if (cmd->name[0] == '.' && cmd->name[1] == '/')
			ft_printf("no such file or directory: %s\n", cmd->name);
		else
			ft_printf("%s: command not found\n", cmd->name);
		exit(0);
	}
	return (free_all(&argvlist, free_all(&pathlist, child_pid)));
}
