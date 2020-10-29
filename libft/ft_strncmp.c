/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:29:17 by gorban            #+#    #+#             */
/*   Updated: 2019/10/14 21:59:12 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			x;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	x = 0;
	if (n < 1)
		return (0);
	while (c1[x] && c2[x] && x < n - 1 && c1[x] == c2[x])
		x++;
	return (c1[x] - c2[x]);
}
