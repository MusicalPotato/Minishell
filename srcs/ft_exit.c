/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:32:08 by igor              #+#    #+#             */
/*   Updated: 2021/03/01 15:48:34 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (!cmd->arg_nbr)
		exit(0);
	while (ft_is_space(cmd->arg[0][i]))
		i++;
	if (cmd->arg[0][i] == '+' || cmd->arg[0][i] == '-')
		i++;
	while (ft_isdigit(cmd->arg[0][i]))
		i++;
	while (cmd->arg[0][i])
	{
		if (cmd->arg[0][i] != ' ' && cmd->arg[0][i] != '\t')
		{
			ft_printf(
			"minishell: exit: %s: numeric argument required\n", cmd->arg[0]);
			exit(-1);
		}
		i++;
	}
	if (cmd->arg_nbr > 1)
		return (exit_write("minishell: exit: too many arguments\n", 0, -2));
	i = ft_atoi(cmd->arg[0]);
	if (i == -1 && !ft_numis_negone(cmd->arg[0]))
		ft_printf(
			"minishell: exit: %s: numeric argument required\n", cmd->arg[0]);
	exit(i);
}
