/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 14:48:42 by igor              #+#    #+#             */
/*   Updated: 2021/01/11 15:49:13 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
int		ft_check_args(t_cmd *cmd, int i)
{
	if (i == 1)
	{
		if (cmd->arg_nbr == 0)
			cmd->arg = ft_stradd_back(cmd->arg, 0, cmd->arg_nbr++);
		if (cmd->arg_nbr > 1 && cmd->arg[1][0] != '>' && cmd->arg[1][0] != '<' )
				return (ft_printf("cd: too many arguments\n"));
	}
	else if (i == 2 && cmd->arg_nbr > 0)
		return (ft_printf("pwd: too many arguments\n"));
	else if (i == 3 && cmd->arg_nbr < 1)
		return (ft_printf("unset: not enough arguments\n"));
	else if (i == 4 && cmd->arg_nbr > 0)
		return (ft_printf("env: too many arguments\n"));
	else if (i == 5 && cmd->arg_nbr > 1)
		return (ft_printf("exit: too many arguments\n"));
	return (1);
}
*/
int		ft_cmd_path_cmp(t_cmd *cmd, char **envp)
{
	char	*paths;
	int		i[3];
	char	**pathlist;
	char	**argvlist;

	i[0] = 1;
	i[2] = 0;
	argvlist = malloc(sizeof(char*) * (cmd->arg_nbr + 2));
	argvlist[0] = ft_strdup(cmd->name);
	if ((i[1] = ft_file_redirect(cmd)) == 0 || i[1] == -1)
		return (i[1]);
	if (i[1] > 0)
		if (!(i[2] = ft_open_close(1, i[1], i[2])))
			return (0);
	while (i[0] <= cmd->arg_nbr && cmd->arg[i[0] - 1][0] != '>')
	{
		argvlist[i[0]] = ft_strdup(cmd->arg[i[0] - 1]);
		(i[0])++;
	}
	argvlist[i[0]] = NULL;
	i[0] = 0;
	pathlist = ft_split(ft_getenv("PATH", envp), ':');
	while (pathlist[i[0]])
	{
		if (!(paths = malloc(1)))
			return (free_all(&pathlist, 0));
		paths[0] = '\0';
		paths = ft_memcat(paths, pathlist[i[0]], 0, ft_strlen(pathlist[i[0]]));
		paths = ft_memcat(paths, "/", ft_strlen(paths), 1);
		paths = ft_memcat(paths, cmd->name, ft_strlen(paths), ft_strlen(cmd->name));
		if (execve(paths, argvlist, envp) != -1)
		{
			if (i[2])
				ft_open_close(2, i[0], i[2]);
			free(paths);
			return (free_all(&pathlist, 1));
		}
		if (i[2])
			ft_open_close(2, i[0], i[2]);
		(i[0])++;
		free(paths);
	}
	return (free_all(&pathlist, -1));
}

int		ft_cmd_cmp(t_cmd *cmd, char ***envp)
{
	if (!ft_strncmp(cmd->name, "echo", 5))
		return (ft_echo(cmd));
	if (!ft_strncmp(cmd->name, "cd", 3))
		return (ft_cd(cmd, *envp));
	else if (!ft_strncmp(cmd->name, "pwd", 4))
		return (ft_pwd(cmd));
	else if (!ft_strncmp(cmd->name, "exit", 5))
		return (ft_exit(cmd));
	else if (cmd->name[0] == '.' && cmd->name[1] == '/')
		return (ft_exec(cmd, *envp));
	else if (cmd->name[0] == '>')
		return (ft_file_create(cmd));
	else if (ft_cmd_path_cmp(cmd, *envp))
		return (1);
	else if (!ft_strncmp(cmd->name, "env", 4))
		return (ft_env(cmd, *envp));
	else if (!ft_strncmp(cmd->name, "unset", 6))
		return (ft_unset(cmd, envp));
	else if (!ft_strncmp(cmd->name, "export", 7))
		return (ft_export(cmd, envp));
	else
		return (exit_write("command not found: ", cmd->name, -1));
}

