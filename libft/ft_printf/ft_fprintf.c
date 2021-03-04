/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 14:46:20 by tkleynts          #+#    #+#             */
/*   Updated: 2021/03/04 14:50:05 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_fprintf(int fd, const char *array, ...)
{
	va_list	ap;
	int		zap;
	int		zaap;
	long	flags[6];

	if (fd < 0)
		return (-1);
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
			zap = ft_parse_write(array, flags, fd);
		array += zap;
	}
	va_end(ap);
	return (flags[5]);
}
