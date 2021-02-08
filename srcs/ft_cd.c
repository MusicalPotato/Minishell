/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:25:46 by igor              #+#    #+#             */
/*   Updated: 2021/01/27 08:16:20 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	errno_sorter(t_cmd *cmd)
{
	printf("%s: ", cmd->name);
	if (errno == EACCES)
		return (exit_write("Permission denied: ", cmd->arg[0], -1));
	else if (errno == ENOENT)
		return (exit_write("No such file or directory: ", cmd->arg[0], -1));
	else
		return (exit_write("Error\n", 0, -1));
}

int	ft_cd(t_cmd *cmd, char ***envp)
{
	errno = 0;
	if (cmd->arg_nbr > 1 && cmd->arg[0][0] != '>' && cmd->arg[1][0] != '>')
		return (exit_write("cd: too many arguments\n", 0, -1));
	if (!cmd->arg_nbr || cmd->arg[0][0] == '>')
		chdir(ft_getenv("HOME", *envp));
	else
		chdir(cmd->arg[0]);
	if (errno)
		return (errno_sorter(cmd));
	ft_putenv(ft_envformat("OLDPWD", ft_getenv("PWD", *envp)), envp);
	ft_putenv(ft_envformat("PWD", getcwd(0, 0)), envp);
	return (1);
}
