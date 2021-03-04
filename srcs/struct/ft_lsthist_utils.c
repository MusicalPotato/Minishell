#include "../../includes/minishell.h"

t_hist	*ft_lstnew_hist(char *content)
{
	t_hist	*list;

	if (!(list = malloc(sizeof(t_hist))))
	{
		ft_freeturn(&content, 0);
		return (0);
	}
	list->line = content;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

int		ft_lstadd_back_hist(t_hist **alst, t_hist *new)
{
	t_hist    *list;

	if (!new)
		return (0);
	if (!(*alst))
	{
		*alst = new;
		return (1);
	}
	list = *alst;
	while (list->next)
		list = list->next;
	list->next = new;
	new->prev = list;
	return (1);
}

int		ft_lstadd_front_hist(t_hist **alst, t_hist *new)
{
	t_hist  *tmp;

	if (!new)
		return (0);
	if (!(*alst))
	{
		if (!(tmp = ft_lstnew_hist(NULL)))
			return (0);
		new->prev = tmp;
		tmp->next = new;
		*alst = tmp;
	}
	else
	{
		tmp = (*alst)->next;
		(*alst)->next = new;
		new->prev = (*alst);
		new->next = tmp;
		if (tmp)
			tmp->prev = new;
	}
	return (1);
}

void	ft_lstclear_hist(t_hist **lst)
{
	t_hist	*l;

	while (*lst)
	{
		l = (*lst)->next;
		if ((*lst)->line)
			free((*lst)->line);
		(*lst)->line = NULL;
		(*lst)->next = NULL;
		(*lst)->prev = NULL;
		free(*lst);
		*lst = l;
	}
	*lst = NULL;
}
