/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:42:04 by gorban            #+#    #+#             */
/*   Updated: 2019/10/18 17:02:59 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
{
	t_list	*result;
	t_list	*l;
	t_list	*temp;

	if (!lst || !f || !del)
		return (0);
	l = lst;
	if (!(result = ft_lstnew((*f)(l->content))))
		return (0);
	l = l->next;
	while (l)
	{
		if (!(temp = ft_lstnew((*f)(l->content))))
		{
			ft_lstclear(&result, del);
			return (0);
		}
		ft_lstadd_back(&result, temp);
		l = l->next;
	}
	return (result);
}
