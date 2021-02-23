/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:25:46 by igor              #+#    #+#             */
/*   Updated: 2021/02/21 14:13:47 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_errno_cd(t_cmd *cmd, t_rdir pipe_rd)
{
	int	ret;
	int	i;

	i = -1;
	ft_close_all(pipe_rd);
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

int	ft_cd(t_cmd *cmd, t_rdir pipe_rd, char ***envp)
{
	char	*pwd;
	char	*value;

	errno = 0;
	if (cmd->arg_nbr > 1 && cmd->arg[0][0] != '>' && cmd->arg[1][0] != '>')
		return (exit_write("minishell: cd: too many arguments\n", 0, 1));
	if (!cmd->arg_nbr || cmd->arg[0][0] == '>')
	{
		value = ft_getenv("HOME", *envp);
		if (!value)
			return (exit_write("minishell: cd: HOME not set\n", 0, 1));
		chdir(ft_getenv("HOME", *envp));
	}
	else if (cmd->arg[0][0] == 0)
		chdir(ft_getenv("PWD", *envp));
	else
		chdir(cmd->arg[0]);
	if (errno)
		return (ft_errno_cd(cmd, pipe_rd));
	ft_putenv(ft_envformat("OLDPWD", ft_getenv("PWD", *envp)), envp, 1);
	pwd = getcwd(0, 0);
	ft_putenv(ft_envformat("PWD", pwd), envp, 1);
	free(pwd);
	return (0);
}
