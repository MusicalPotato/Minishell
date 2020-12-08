/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:50:48 by igor              #+#    #+#             */
/*   Updated: 2020/12/08 12:44:44 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_pwd(t_cmd *cmd)
{
	char *str;
	int i;
	int std;

	std = 0;
	str = getcwd(0, 0);
	if ((i = ft_file_redirect(cmd)) == 0 || i == -1)
		return (i);
	if (i > 0)
		if (!(std = ft_open_close(1, i, std)))
			return (0);
	ft_printf("%s\n", str);
	free(str);
	if (std)
		return (ft_open_close(2, i, std));
	return (1);
}
