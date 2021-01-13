/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:25:46 by igor              #+#    #+#             */
/*   Updated: 2021/01/12 16:12:03 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_cmd *cmd, char **envp)
{
	int i;

	i = 0;
	if (cmd->arg_nbr > 1 && cmd->arg[0][0] != '>' && cmd->arg[1][0] != '>')
		return (exit_write("cd: too many arguments\n", 0, -1));
	if (!cmd->arg_nbr || cmd->arg[0][0] == '>')
		i = chdir(ft_getenv("HOME", envp));
	else
		i = chdir(cmd->arg[0]);
	if (errno == EACCES)
		return (exit_write("cd: Permission denied: ", cmd->arg[0], -1));
	else if (errno == ENOENT)
		return (exit_write("cd: No such file or directory: ", cmd->arg[0], -1));
	else if (errno)
		return (exit_write("cd: Error", 0, -1));
	return (1);
}
