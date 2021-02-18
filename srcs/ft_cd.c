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

int	ft_cd(t_cmd *cmd, char ***envp)
{
	char	*pwd;
	errno = 0;
	if (cmd->arg_nbr > 1 && cmd->arg[0][0] != '>' && cmd->arg[1][0] != '>')
		return (exit_write("cd: too many arguments\n", 0, 255));
	if (!cmd->arg_nbr || cmd->arg[0][0] == '>')
		chdir(ft_getenv("HOME", *envp));
	else
		chdir(cmd->arg[0]);
	if (errno)
		return (ft_errno(cmd));
	ft_putenv(ft_envformat("OLDPWD", ft_getenv("PWD", *envp)), envp, 1);
	pwd = getcwd(0, 0);
	ft_putenv(ft_envformat("PWD", pwd), envp, 1);
	free(pwd);
	return (0);
}
