/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 17:13:44 by ijacquet          #+#    #+#             */
/*   Updated: 2021/03/05 16:53:25 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*ft_lstnew_cmd(char *content)
{
	t_cmd	*list;

	if (!content)
		return (0);
	if (!(list = malloc(sizeof(t_cmd))))
	{
		ft_freeturn(&content, 1);
		return (0);
	}
	list->line = content;
	list->argv = NULL;
	list->argc = 0;
	list->next = 0;
	return (list);
}

int		ft_lstadd_back_cmd(t_cmd **alst, t_cmd *new)
{
	t_cmd	*l;

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

void	ft_lstclear_cmd(t_cmd **lst)
{
	t_cmd	*l;
	int		x;

	x = 0;
	while (*lst)
	{
		l = (*lst)->next;
		free((*lst)->line);
		(*lst)->line = NULL;
		while (x < (*lst)->argc)
		{
			free((*lst)->argv[x]);
			(*lst)->argv[x] = NULL;
			x++;
		}
		free((*lst)->argv);
		(*lst)->argv = NULL;
		(*lst)->argc = 0;
		(*lst)->next = NULL;
		free(*lst);
		*lst = l;
	}
	*lst = NULL;
}
