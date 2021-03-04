/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errno.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 12:34:31 by igor              #+#    #+#             */
/*   Updated: 2021/03/04 15:59:13 by tkleynts         ###   ########.fr       */
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
	i = 0;
	ft_close_all(pipe_rd);
	while (cmd->argc >= ++i + 1)
		if (cmd->argv[i][0] == '>' || cmd->argv[i][0] == '<')
			return (ft_errno2(cmd));
	if (errno == EISDIR && (ret = 126))
		ft_fprintf(2, "minishell: %s: is a directory\n", cmd->argv[0]);
	else if (errno == EACCES && (ret = 126))
		ft_fprintf(2, "minishell: %s: Permission denied\n", path);
	else if (errno == ENOENT && (ret = 127))
	{
		if (ft_hasslash(cmd->argv[0]) || emsg == 2)
			ft_fprintf(2,
				"minishell: %s: No such file or directory\n", cmd->argv[0]);
		else
			ft_fprintf(2, "minishell: %s: command not found\n", cmd->argv[0]);
	}
	else if (errno == ENOEXEC && (ret = 126))
		ft_fprintf(2, "minishell: %s: Exec format error\n", cmd->argv[0]);
	return (ret);
}

int	ft_errno2(t_cmd *cmd)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (cmd->argc >= i++ + 1)
		if (cmd->argv[i][0] == '>' || cmd->argv[i][0] == '<')
			break ;
	if (errno == EISDIR && (ret = 126))
		ft_fprintf(2, "minishell: %s: is a directory\n", cmd->argv[0]);
	else if (errno == EACCES && (ret = 1))
		ft_fprintf(2, "minishell: %s: Permission denied\n", cmd->argv[2]);
	else if (errno == ENOENT && (ret = 1))
	{
		if (cmd->argv[0][0] == '<')
			ft_fprintf(2, "minishell: %s: No such file or directory\n",
					cmd->argv[1]);
		else if (cmd->argv[i][0] != '>' && cmd->argv[i][0] != '<')
			ft_fprintf(2, "minishell: %s: %s: No such file or directory\n",
					cmd->argv[0], cmd->argv[1]);
		else
			ft_fprintf(2, "minishell: %s: No such file or directory\n",
					cmd->argv[i + 1]);
	}
	return (ret);
}
