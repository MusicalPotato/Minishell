/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:26:56 by gorban            #+#    #+#             */
/*   Updated: 2019/10/14 17:37:59 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*h;
	char	*n;
	size_t	a;
	size_t	b;

	a = -1;
	h = (char *)haystack;
	n = (char *)needle;
	if (!(*n))
		return (h);
	while (h[++a] && a <= len)
	{
		b = 0;
		while ((h[a + b] == n[b] || n[b] == 0) && (a + b) <= len)
		{
			if (n[b] == 0)
			{
				while (a--)
					h++;
				return (h);
			}
			b++;
		}
	}
	return (0);
}
