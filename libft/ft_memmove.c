/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:02:36 by gorban            #+#    #+#             */
/*   Updated: 2019/10/16 21:09:27 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			x;
	unsigned char	*dsttemp;
	unsigned char	*srctemp;

	if (!(dst || src))
		return (0);
	if (dst == src)
		return (dst);
	dsttemp = (unsigned char *)dst;
	srctemp = (unsigned char *)src;
	x = 0;
	if (srctemp > dsttemp)
		while (x < len)
		{
			dsttemp[x] = srctemp[x];
			x++;
		}
	else
		while (len-- > 0)
			dsttemp[len] = srctemp[len];
	return (dst);
}
