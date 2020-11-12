/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:22:53 by nlaurids          #+#    #+#             */
/*   Updated: 2020/11/10 13:57:39 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_exec(t_cmd *cmd, char **envp)
{
	char	**argv_ms;
	int		status;
	int		i;

	i = 1;
	argv_ms = malloc(sizeof(char*) * (cmd->arg_nbr + 2));
	argv_ms[0] = ft_strdup(cmd->name);
	while (i <= cmd->arg_nbr)
	{
		argv_ms[i] = ft_strdup(cmd->arg[i - 1]);
		i++;
	}
	argv_ms[i] = NULL;
	if (fork() == -1)
		return (free_all(&argv_ms, 0));
	if (wait(&status) < 0)
		if (execve(cmd->name, argv_ms, envp) < 0)
		{
			ft_printf("no such file or directory: %s\n", cmd->name);
			return (free_all(&argv_ms, 0));
		}
	return (free_all(&argv_ms, 1));
}
