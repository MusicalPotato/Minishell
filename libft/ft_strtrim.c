/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:37:47 by gorban            #+#    #+#             */
/*   Updated: 2019/10/16 16:03:52 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_istrim(char c, char const *set)
{
	while (*set != 0)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	ft_lentrim(char const *s1, char const *set, int len)
{
	while (ft_istrim(s1[len - 1], set))
		len--;
	while (ft_istrim(*s1, set))
	{
		len--;
		s1++;
	}
	if (len < 0)
		return (0);
	return (len);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		size;
	int		len;
	int		x;

	x = 0;
	if (!(s1) || !set)
		return (0);
	len = ft_strlen(s1);
	size = ft_lentrim(s1, set, len);
	if (!(str = malloc(sizeof(char) * size + 1)))
		return (0);
	while (ft_istrim(s1[x], set))
		x++;
	str[size] = 0;
	while (size--)
	{
		str[size] = s1[size + x];
	}
	return (str);
}
