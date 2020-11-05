/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:39:34 by gorban            #+#    #+#             */
/*   Updated: 2020/11/05 14:17:14 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		x;
	char	*copy;

	x = 0;
	while (s1 && s1[x])
		x++;
	if (!(copy = malloc(sizeof(char) * x + 1)))
		return (0);
	x = 0;
	while (s1 && s1[x])
	{
		copy[x] = s1[x];
		x++;
	}
	copy[x] = 0;
	return (copy);
}
