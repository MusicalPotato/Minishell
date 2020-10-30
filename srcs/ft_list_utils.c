/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:36:42 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/30 13:49:55 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_line	*ft_lstnew_line(char *content)
{
	t_line	*list;

	if (!content)
		return (0);
	if (!(list = malloc(sizeof(t_line))))
		return (0);
	list->line = content;
	list->cmd_nbr = 0;
	list->cmd = 0;
	list->next = 0;
	return (list);
}

int		ft_lstadd_back_line(t_line **alst, t_line *new)
{
	t_line	*l;

	if (!(alst) || !(new))
		return (0);
	if (!(*alst))
	{
		*alst = new;
		return (1);
	}
	l = *alst;
	while (l->next)
		l = l->next;
	l->next = new;
	return (1);
}
