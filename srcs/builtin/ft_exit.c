/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:32:08 by igor              #+#    #+#             */
/*   Updated: 2021/03/04 16:00:46 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_numis_negone(char *num)
{
	int	i;

	i = 0;
	if (num[i] != '-')
		return (0);
	i++;
	while (num[i] == '0')
		i++;
	if (num[i] != '1')
		return (0);
	i++;
	if (num[i])
		return (0);
	return (1);
}

int	ft_exit(t_cmd *cmd, int i)
{
	if (cmd && cmd->argc)
	{
		while (ft_is_space(cmd->argv[1][i]))
			i++;
		if (cmd->argv[1][i] == '+' || cmd->argv[1][i] == '-')
			i++;
		while (ft_isdigit(cmd->argv[1][i]))
			i++;
		while (cmd->argv[1][i] == ' ' || cmd->argv[1][i] == '\t')
			i++;
		if (cmd->argv[1][i] != 0)
		{
			ft_fprintf(2,
			"minishell: exit: %s: numeric argument required\n", cmd->argv[1]);
			ft_lstclear_data(&g_data);
			exit(-1);
		}
		if (cmd->argc > 1)
			return (exit_write("minishell: exit: too many arguments\n", 0, -2));
		if ((i = ft_atoi(cmd->argv[1])) == -1 && !ft_numis_negone(cmd->argv[1]))
			ft_fprintf(2,
			"minishell: exit: %s: numeric argument required\n", cmd->argv[1]);
	}
	ft_lstclear_data(&g_data);
	exit(i);
}
