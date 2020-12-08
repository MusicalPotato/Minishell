/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 14:48:42 by igor              #+#    #+#             */
/*   Updated: 2020/12/08 09:57:54 by igor             ###   ########.fr       */
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
int		ft_cmd_cmp(t_cmd *cmd, char **envp)
{
//	if (!ft_strncmp(cmd->name, "echo", 5))
//		ft_echo(cmd);
	if (!ft_strncmp(cmd->name, "cd", 3))
		return (ft_cd(cmd));
	else if (!ft_strncmp(cmd->name, "pwd", 4))
		return (ft_pwd(cmd));
//	else if (!ft_strncmp(cmd->name, "export", 7))
//		ft_export(cmd);
//	else if (!ft_strncmp(cmd->name, "unset", 6) && ft_check_args(cmd, 3))
//		ft_unset(cmd);
//	else if (!ft_strncmp(cmd->name, "env", 4) && ft_check_args(cmd, 4))
//		ft_env(cmd);
	else if (!ft_strncmp(cmd->name, "exit", 5))
		return (ft_exit(cmd));
	else if (cmd->name[0] == '.' && cmd->name[1] == '/')
		return (ft_exec(cmd, envp));
	else if (cmd->name[0] == '>')
		return (ft_file_create(cmd));
	else
		return (exit_write("command not found: ", cmd->name, -1));
}
