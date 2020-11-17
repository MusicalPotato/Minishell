/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:25:46 by igor              #+#    #+#             */
/*   Updated: 2020/11/16 15:10:23 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(char *path)
{
//	char	*home;
//
//	home = variable d'env HOME
//	if ~ dans path alors remplacer ~ par home
	if (!path)
	{
//		chdir(home);
	}
	else
		chdir(path);
//	faire les erreur + msg en fct du nbr ret chdir (errno tout ca)
	return (1);
}
