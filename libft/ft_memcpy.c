/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:45:20 by gorban            #+#    #+#             */
/*   Updated: 2019/10/16 18:26:31 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long	x;
	char			*dsttemp;
	char			*srctemp;

	if (!(src || dst))
		return (0);
	dsttemp = (char *)dst;
	srctemp = (char *)src;
	x = 0;
	while (x < n)
	{
		dsttemp[x] = srctemp[x];
		x++;
	}
	return (dst);
}
