/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 10:20:40 by gorban            #+#    #+#             */
/*   Updated: 2019/10/18 18:16:39 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	x;
	size_t	slen;

	if (!(s))
		return (0);
	slen = ft_strlen(s);
	x = 0;
	if (start > slen)
		len = 0;
	else if (start + len > slen)
		len = slen - start;
	if ((str = malloc(sizeof(char) * len + 1)))
	{
		while (x < len)
		{
			str[x] = s[start + x];
			x++;
		}
		str[len] = 0;
	}
	return (str);
}
