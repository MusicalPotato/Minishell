/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:22:53 by nlaurids          #+#    #+#             */
/*   Updated: 2020/12/08 12:56:20 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_exec(t_cmd *cmd, char **envp)
{
	char	**argv_ms;
	int		status;
	int		i;
	int		j;
	int		std;

	std = 0;
	i = 1;
	argv_ms = malloc(sizeof(char*) * (cmd->arg_nbr + 2));
	argv_ms[0] = ft_strdup(cmd->name);
	if ((j = ft_file_redirect(cmd)) == 0 || j == -1)
		return (j);
	if (j > 0)
		if (!(std = ft_open_close(1, j, std)))
			return (0);
	while (i <= cmd->arg_nbr && cmd->arg[i - 1][0] != '>')
	{
		argv_ms[i] = ft_strdup(cmd->arg[i - 1]);
		i++;
	}
	argv_ms[i] = NULL;
	if (fork() == -1)
	{
		if (std)
			ft_open_close(2, i, std);
		return (free_all(&argv_ms, 0));
	}
	if (wait(&status) < 0)
		if (execve(cmd->name, argv_ms, envp) < 0)
		{
			ft_printf("no such file or directory: %s\n", cmd->name);
			if (std)
				ft_open_close(2, i, std);
			return (free_all(&argv_ms, 0));
		}
	if (std)
		ft_open_close(2, i, std);
	return (free_all(&argv_ms, 1));
}
