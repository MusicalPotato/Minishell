/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 04:05:02 by igor              #+#    #+#             */
/*   Updated: 2021/01/12 16:29:09 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_echo(t_cmd *cmd)
{
    int	nl;
    int	i;

    i = 0;
    nl = 1;
    if (cmd->arg_nbr && !(ft_strncmp(cmd->arg[i], "-n", 3)))
    {
		nl = 0;
		i++;
    }
    while (i < cmd->arg_nbr)
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