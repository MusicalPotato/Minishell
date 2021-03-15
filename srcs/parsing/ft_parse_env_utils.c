/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 00:22:54 by igor              #+#    #+#             */
/*   Updated: 2021/03/16 00:22:55 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_countbs(char *str)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\\')
			n++;
		i++;
	}
	return (n);
}

t_ed	*ft_lstnew_envdata(void)
{
	t_ed	*list;

	if (!(list = malloc(sizeof(t_ed))))
		return (0);
	list->var = NULL;
	list->s_var = 0;
	list->val = NULL;
	list->s_val = 0;
	list->count = 0;
	return (list);
}
