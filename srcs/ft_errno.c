/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errno.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 12:34:31 by igor              #+#    #+#             */
/*   Updated: 2021/03/01 13:14:10 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_hasslash(char *string)
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

int	ft_errno_exec(t_cmd *cmd, t_rdir pipe_rd, char *path, int emsg)
{
	int	ret;
	int	i;

	ret = 0;
	i = -1;
	ft_close_all(pipe_rd);
	while (cmd->arg_nbr > ++i + 1)
		if (cmd->arg[i][0] == '>' || cmd->arg[i][0] == '<')
			return (ft_errno2(cmd));
	if (errno == EISDIR && (ret = 126))
		ft_printf("minishell: %s: is a directory\n", cmd->name);
	else if (errno == EACCES && (ret = 126))
		ft_printf("minishell: %s: Permission denied\n", path);
	else if (errno == ENOENT && (ret = 127))
	{
		if (ft_hasslash(cmd->name) || emsg == 2)
			ft_printf("minishell: %s: No such file or directory\n", cmd->name);
		else
			ft_printf("minishell: %s: command not found\n", cmd->name);
	}
	else if (errno == ENOEXEC && (ret = 126))
		ft_printf("minishell: %s: Exec format error\n", cmd->name);
	return (ret);
}

int	ft_errno2(t_cmd *cmd)
{
	int	ret;
	int	i;

	ret = 0;
	i = -1;
	while (cmd->arg_nbr > i++ + 1)
		if (cmd->arg[i][0] == '>' || cmd->arg[i][0] == '<')
			break ;
	if (errno == EISDIR && (ret = 126))
		ft_printf("minishell: %s: is a directory\n", cmd->name);
	else if (errno == EACCES && (ret = 1))
		ft_printf("minishell: %s: Permission denied\n", cmd->arg[1]);
	else if (errno == ENOENT && (ret = 1))
	{
		if (cmd->name[0] == '<')
			ft_printf("minishell: %s: No such file or directory\n",
					cmd->arg[0]);
		else if (cmd->arg[i][0] != '>' && cmd->arg[i][0] != '<')
			ft_printf("minishell: %s: %s: No such file or directory\n",
					cmd->name, cmd->arg[0]);
		else
			ft_printf("minishell: %s: No such file or directory\n",
					cmd->arg[i + 1]);
	}
	return (ret);
}
