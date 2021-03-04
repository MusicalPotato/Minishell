/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:25:46 by igor              #+#    #+#             */
/*   Updated: 2021/03/04 15:59:54 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_errno_cd(t_cmd *cmd, t_rdir pipe_rd)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	ft_close_all(pipe_rd);
	while (cmd->argc > i && ++i)
		if (cmd->argv[i][0] == '>' || cmd->argv[i][0] == '<')
			break ;
	if (errno == EISDIR && (ret = 126))
		ft_fprintf(2, "minishell: %s: is a directory\n", cmd->argv[0]);
	else if (errno == EACCES && (ret = 126))
		ft_fprintf(2, "minishell: %s: %s: Permission denied\n",
				cmd->argv[0], cmd->argv[1]);
	else if (errno == ENOENT && (ret = 1))
	{
		if (cmd->argv[i][0] != '>' && cmd->argv[i][0] != '<')
			ft_fprintf(2, "minishell: %s: %s: No such file or directory\n",
					cmd->argv[0], cmd->argv[1]);
		else
			ft_fprintf(2, "minishell: %s: No such file or directory\n",
					cmd->argv[i + 1]);
	}
	return (ret);
}

int	ft_cd(t_cmd *cmd, t_rdir pipe_rd, char ***envp)
{
	char	*pwd;
	char	*value;

	errno = 0;
	if (cmd->argc > 1 && cmd->argv[1][0] != '>' && cmd->argv[2][0] != '>')
		return (exit_write("minishell: cd: too many arguments\n", 0, 1));
	if (!cmd->argc || cmd->argv[1][0] == '>')
	{
		value = ft_getenv("HOME", *envp);
		if (!value)
			return (exit_write("minishell: cd: HOME not set\n", 0, 1));
		chdir(ft_getenv("HOME", *envp));
	}
	else if (cmd->argv[1][0] == 0)
		chdir(ft_getenv("PWD", *envp));
	else
		chdir(cmd->argv[1]);
	if (errno)
		return (ft_errno_cd(cmd, pipe_rd));
	ft_putenv(ft_envformat("OLDPWD", ft_getenv("PWD", *envp)), envp, 1);
	pwd = getcwd(0, 0);
	ft_putenv(ft_envformat("PWD", pwd), envp, 1);
	free(pwd);
	return (0);
}
