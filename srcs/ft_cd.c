/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:25:46 by igor              #+#    #+#             */
/*   Updated: 2020/12/08 10:06:34 by igor             ###   ########.fr       */
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
			if (!(i = ft_file_redirect(cmd)))
				return (0);
			close (i);
			break ;
		}
		i++;
	}
	if (cmd->arg_nbr > 1 && cmd->arg[0][0] != '>' && cmd->arg[1][0] != '>')
		return (exit_write("cd: too many arguments\n", 0, -1));
	if (!cmd->arg_nbr || cmd->arg[0][0] == '>')
	{
//		chdir(home);
	}
	else
		chdir(cmd->arg[0]);
//	faire les erreur + msg en fct du nbr ret chdir (errno tout ca)
	return (1);
}
