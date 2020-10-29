/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:00:22 by gorban            #+#    #+#             */
/*   Updated: 2019/11/21 17:19:12 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parse_write(const char *array, long flags[6])
{
	int	zap;

	zap = 0;
	while (*(array + zap) && *(array + zap) != '%')
		zap++;
	ft_write(1, (char *)array, zap, flags);
	return (zap);
}

int	ft_printf(const char *array, ...)
{
	va_list	ap;
	int		zap;
	int		zaap;
	long	flags[6];

	va_start(ap, array);
	while (*array)
	{
		if (*array == '%')
		{
			if (!(zap = check_comb(ap, (char *)(array + 1), flags)))
				return (-1);
			if ((zaap = parse(ap, flags)) < 0)
				return (-1);
		}
		else
			zap = ft_parse_write(array, flags);
		array += zap;
	}
	va_end(ap);
	return (flags[5]);
}
