/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 17:13:44 by ijacquet          #+#    #+#             */
/*   Updated: 2020/11/05 17:13:49 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*ft_lstnew_cmd(char *content)
{
	t_cmd	*list;

	if (!(list = malloc(sizeof(t_cmd))))
		return (0);
	list->cmd_id = 0;
	list->optn_id = 0;
	list->msg = malloc(0);
	list->msg_nbr = -1;
	list->next = 0;
	if (!content)
		return (0);
	list->cmd = content;
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
	t_cmd	*t;

	if (lst)
	{
		l = *lst;
		while (l)
		{
			t = l;
			free(l->cmd);
			l->cmd = NULL;
			while (*(l->msg))
			{
				free(*(l->msg));
				*(l->msg) = NULL;
				(*(l->msg))++;
			}
			free(l->msg);
			l->msg = NULL;
			free(l);
			l = t->next;
		}
		*lst = NULL;
	}
}
