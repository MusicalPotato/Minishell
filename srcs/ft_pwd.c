/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:50:48 by igor              #+#    #+#             */
/*   Updated: 2020/12/08 09:01:46 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_pwd(t_cmd *cmd)
{
	char *str;
	int i;
	int std;

	i = 0;
	std = 0;
	str = getcwd(0, 0);
	while (i < cmd->arg_nbr)
	{
		if (cmd->arg[i][0] == '>')
		{
			if ((i = ft_file_redirect(cmd)) < 1)
				return (i);
			if (!(std = ft_open_close(1, i, std)))
				return (0);
			break;
		}
		i++;
	}
	ft_printf("%s\n", str);
	free(str);
	if (std)
		return (ft_open_close(2, i, std));
	return (1);
}
