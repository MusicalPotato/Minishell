/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:50:48 by igor              #+#    #+#             */
/*   Updated: 2020/12/07 16:48:45 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_pwd(t_cmd *cmd)
{
	char *str;
	int i;
	int std;

	i = 0;
	str = 0;
	str = getcwd(str, ft_strlen(str));
	while (i < cmd->arg_nbr)
	{
		if (cmd->arg[i][0] == '>')
		{
			std = dup(1);
			if ((i = ft_file_redirect(cmd)) < 1)
				return (i);
			ft_printf("%s\n", str);
			free (str);
			close(i);
			dup2(std, 1);
			close(std);
			return (1);
		}
		i++;
	}
	ft_printf("%s\n", str);
	free (str);
	return (1);
}
