/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 04:05:02 by igor              #+#    #+#             */
/*   Updated: 2021/03/01 13:13:06 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_arg(t_cmd *cmd)
{
	int	i;
	int	a;

	i = 1;
	while (i <= cmd->argc)
	{
		if (!ft_strncmp(cmd->argv[i], "-n", 2))
		{
			a = 1;
			while (cmd->argv[i][a] == 'n')
				a++;
			if (cmd->argv[i][a] && cmd->argv[i][a] != 'n')
				return (i);
		}
		else
			return (i);
		i++;
	}
	return (i);
}

int	ft_echo(t_cmd *cmd)
{
	int	nl;
	int	i;
	int	j;

	i = ft_check_arg(cmd);
	j = 0;
	nl = 1;
	if (cmd->argc && i > 1)
		nl = 0;
	while (i <= cmd->argc)
	{
		if (cmd->argv[i][0] == '>' || cmd->argv[i][0] == '<')
			i += 2;
		if (i <= cmd->argc && cmd->argv[i][0] != '>' && cmd->argv[i][0] != '<')
		{
			if (i <= cmd->argc && j > 0)
				ft_printf(" ");
			ft_printf("%s", cmd->argv[i]);
			i++;
			j = 1;
		}
	}
	if (nl)
		ft_printf("\n");
	return (0);
}
