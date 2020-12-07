/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:25:46 by igor              #+#    #+#             */
/*   Updated: 2020/11/24 11:26:50 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_cmd *cmd)
{
	int i;
//	char	*home;
//
//	home = variable d'env HOME
//	if ~ dans path alors remplacer ~ par home
	i = 0;
	while (i < cmd->arg_nbr)
	{
		if (cmd->arg[i][0] == '>')
		{
			if (!(ft_file_redirect(cmd, NULL)))
				return (0);
			break ;
		}
		i++;
	}
	if (!cmd->arg_nbr)
	{
//		chdir(home);
	}
	else
		chdir(cmd->arg[0]);
//	faire les erreur + msg en fct du nbr ret chdir (errno tout ca)
	return (1);
}
