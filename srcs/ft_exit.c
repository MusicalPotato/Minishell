/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 11:19:37 by igor              #+#    #+#             */
/*   Updated: 2020/12/07 17:27:42 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     ft_exit(t_cmd *cmd)
{
    int i;
    int j;

	i = 0;
	while (i < cmd->arg_nbr)
	{
		if (cmd->arg[i][0] == '>')
        {
			if ((j = ft_file_redirect(cmd)) < 1)
                return (j);
            break ;
        }
        i++;
	}
    return (0);
}