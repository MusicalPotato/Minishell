/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:31:34 by gorban            #+#    #+#             */
/*   Updated: 2019/10/16 19:07:14 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*l;

	if (!(alst) || !(new))
		return ;
	if (!(*alst))
		return ;
	l = *alst;
	while (l->next)
		l = l->next;
	l->next = new;
}
