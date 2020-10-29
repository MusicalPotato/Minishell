/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:12:03 by gorban            #+#    #+#             */
/*   Updated: 2019/11/26 08:34:08 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** flags[0] = .
** flags[1] = 0
** flags[2] = width
** flags[3] = -
** flags[4] = specifier
** flags[5] = return value
*/

static int	check_late(va_list ap, char *array, long flags[6], int zap)
{
	if (*(array + zap) == '0')
	{
		flags[1] = 1;
		if (*(array + zap + 1) == '*')
			flags[2] = va_arg(ap, int);
		else if (flags[2] == 0)
			flags[2] = ft_atoi(array + zap + 1);
	}
	else if (*(array + zap) == '-' && (flags[3] = 1))
	{
		flags[2] = (*(array + zap + 1) == '*') ? va_arg(ap, int) :
				ft_atoi(array + zap + 1);
	}
	else if (*(array + zap) == '.')
	{
		if (*(array + zap + 1) == '*')
			flags[0] = va_arg(ap, int);
		else
		{
			flags[0] = ft_atoi(array + zap + 1);
			while (ft_isdigit(*(array + 1 + zap)))
				zap++;
		}
	}
	return (zap);
}

static int	check_early(va_list ap, char *array, long flags[6], int zap)
{
	if (*(array + zap) == '*')
	{
		flags[2] = va_arg(ap, int);
		zap++;
		if (ft_isdigit(*(array + zap)))
			flags[2] = ft_atoi(array + zap);
		while (ft_isdigit(*(array + zap)))
			zap++;
	}
	else
	{
		flags[2] = ft_atoi(array + zap);
		while (ft_isdigit(*(array + zap)))
			zap++;
	}
	return (zap);
}

int			check_comb(va_list ap, char *array, long flags[6])
{
	int	zap;

	zap = 0;
	ft_bzero(flags, 4 * sizeof(long));
	flags[0] = -1;
	if (*(array + zap) != '0' && *(array + zap) != '-')
		zap = check_early(ap, array, flags, zap);
	while (ft_isdigit(*(array + zap)) || ft_isflag(*(array + zap)) ||
	ft_isspecifier(*(array + zap)))
	{
		zap = check_late(ap, array, flags, zap);
		if (ft_isspecifier(*(array + zap)))
		{
			if (flags[2] < 0)
			{
				flags[2] *= -1;
				flags[3] = 1;
			}
			flags[4] = *(array + zap);
			return (zap + 2);
		}
		zap++;
	}
	return (0);
}

int			parse(va_list ap, long flags[6])
{
	int	r;

	r = -1;
	if (flags[4] == 'i' || flags[4] == 'd')
		r = parse_int(va_arg(ap, int), flags);
	else if (flags[4] == 'u')
		r = parse_int(va_arg(ap, unsigned int), flags);
	else if (flags[4] == 'c')
		r = parse_char(va_arg(ap, int), flags);
	else if (flags[4] == '%')
		r = parse_char('%', flags);
	else if (flags[4] == 's')
		r = parse_string(va_arg(ap, char*), flags);
	else if (flags[4] == 'p')
		r = parse_address(ft_ultoa_base(va_arg(ap, unsigned long long),
					"0123456789abcdef"), flags);
	else if (flags[4] == 'x')
		r = parse_hex(ft_ultoa_base(va_arg(ap, unsigned int),
					"0123456789abcdef"), flags);
	else if (flags[4] == 'X')
		r = parse_hex(ft_ultoa_base(va_arg(ap, unsigned int),
					"0123456789ABCDEF"), flags);
	return (r);
}
