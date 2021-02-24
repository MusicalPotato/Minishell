/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errno.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 12:34:31 by igor              #+#    #+#             */
/*   Updated: 2021/02/23 15:32:06 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_hasslash(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int ft_errno_exec(t_cmd *cmd, t_rdir pipe_rd, char *path, int emsg)
{
	int	ret;
	int	i;

	i = -1;
	ft_close_all(pipe_rd);
	while (cmd->arg_nbr > ++i + 1)
		if (cmd->arg[i][0] == '>' || cmd->arg[i][0] == '<')
			return (ft_errno2(cmd));
	if (errno == EISDIR)
	{
		ft_printf("minishell: %s: is a directory\n", cmd->name);
		ret = 126;
	}
	else if (errno == EACCES)
	{
		ft_printf("minishell: %s: Permission denied\n", path);
		ret = 126;
	}
	else if (errno == ENOENT)
	{
		if (ft_hasslash(cmd->name) || emsg == 2)
			ft_printf("minishell: %s: No such file or directory\n", cmd->name);
		else
			ft_printf("minishell: %s: command not found\n", cmd->name);
		ret = 127;
	}
	else if (errno == ENOEXEC)
	{
		ft_printf("minishell: %s: Exec format error\n", cmd->name);
		ret = 126;
	}
	else
		return (0);
	return (ret);
}

int	ft_errno2(t_cmd *cmd)
{
	int	ret;
	int	i;

	i = -1;
	while (cmd->arg_nbr > i + 1 && ++i)
		if (cmd->arg[i][0] == '>' || cmd->arg[i][0] == '<')
			break ;
	if (errno == EISDIR)
	{
		ft_printf("minishell: %s: is a directory\n", cmd->name);
		ret = 126;
	}
	else if (errno == EACCES)
	{
		ft_printf("minishell: %s: %s: Permission denied\n", cmd->name, cmd->arg[0]);
		ret = 126;
	}
	else if (errno == ENOENT)
	{
		if (cmd->name[0] == '<')
			ft_printf("minishell: %s: No such file or directory\n", cmd->arg[0]);
		else if (cmd->arg[i][0] != '>' && cmd->arg[i][0] != '<')
			ft_printf("minishell: %s: %s: No such file or directory\n", cmd->name, cmd->arg[0]);
		else
			ft_printf("minishell: %s: No such file or directory\n", cmd->arg[i + 1]);
		ret = 1;
	}
	else
		return (0);
	return (ret);
}