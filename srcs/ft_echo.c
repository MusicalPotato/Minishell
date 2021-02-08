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

int	ft_echo(t_cmd *cmd)
{
	int	nl;
	int	i;

	i = 0;
	nl = 1;
	if (cmd->arg_nbr && !(ft_strncmp(cmd->arg[i], "-n", 3)) && i++)
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
