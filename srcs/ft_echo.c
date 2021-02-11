/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 04:05:02 by igor              #+#    #+#             */
/*   Updated: 2021/02/04 13:52:03 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_arg(t_cmd *cmd)
{
	int	i;
	int	a;

	i = 0;
	while (i < cmd->arg_nbr)
	{
		if (!ft_strncmp(cmd->arg[i], "-n", 2))
		{
			a = 1;
			while (cmd->arg[i][a] == 'n')
				a++;
			if (cmd->arg[i][a] && cmd->arg[i][a] != 'n')
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

	i = ft_check_arg(cmd);
	nl = 1;
	if (cmd->arg_nbr && (i = ft_check_arg(cmd)))
		nl = 0;
	while (i < cmd->arg_nbr && cmd->arg[i][0] != '<')
	{
		if (cmd->arg[i][0] == '>')
			i += 2;
		else
		{
			ft_printf("%s", cmd->arg[i]);
			i++;
			if (i < cmd->arg_nbr)
				ft_printf(" ");
		}
	}
	if (nl)
		ft_printf("\n");
	return (1);
}
