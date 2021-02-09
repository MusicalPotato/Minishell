/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstline_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:36:42 by ijacquet          #+#    #+#             */
/*   Updated: 2021/02/08 20:17:50 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	*ft_lstnew_line(char *content)
{
	t_data	*list;

	if (!content)
		return (0);
	if (!(list = malloc(sizeof(t_data))))
	{
		ft_freeturn(&content, 0);
		return (0);
	}
	list->line = content;
	list->cmd = 0;
	list->next = 0;
	return (list);
}

int		ft_lstadd_back_line(t_data **alst, t_data *new)
{
	t_data	*l;

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

void	ft_lstclear_line(t_data **lst)
{
	t_data	*l;

	while (*lst)
	{
		l = (*lst)->next;
		free((*lst)->line);
		(*lst)->line = NULL;
		ft_lstclear_cmd(&((*lst)->cmd));
		(*lst)->next = NULL;
		free(*lst);
		*lst = l;
	}
	*lst = NULL;
}
