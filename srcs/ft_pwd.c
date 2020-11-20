/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:50:48 by igor              #+#    #+#             */
/*   Updated: 2020/11/20 03:02:04 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_pwd(t_cmd *cmd)
{
	char *str;
	int i;

	i = 0;
	str = 0;
	str = getcwd(str, ft_strlen(str));
	while (i < cmd->arg_nbr)
	{
		if (cmd->arg[i][0] == '>')
			return (ft_file_redirect(cmd, str));
		i++;
	}
	ft_printf("%s\n", str);
	free (str);
	return (1);
}
