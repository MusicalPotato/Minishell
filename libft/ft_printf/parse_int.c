/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 13:20:18 by gorban            #+#    #+#             */
/*   Updated: 2019/11/25 13:20:19 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse2_int(long leint, long flags[6], int len)
{
	int	pre;

	while (flags[3] == 0 && flags[2] > len && flags[2] > flags[0])
	{
		if (flags[1] == 0)
			ft_write(1, " ", 1, flags);
		else
			ft_write(1, "0", 1, flags);
		flags[2]--;
	}
	if (leint < 0 && flags[0] >= 0)
	{
		ft_write(1, "-", 1, flags);
		leint *= -1;
	}
	pre = flags[0];
	while (pre-- > len)
		ft_write(1, "0", 1, flags);
	pre++;
	if (leint != 0 || pre != 0)
		ft_write_nbr(1, leint, flags);
	while (flags[3] == 1 && flags[2] > len && flags[2]-- > flags[0])
		ft_write(1, " ", 1, flags);
	return (1);
}

int	parse_int(long leint, long flags[6])
{
	int	len;

	if (flags[0] >= 0)
		flags[1] = 0;
	len = ft_intlen(leint);
	if (leint < 0 && (flags[1] == 1 || flags[3] == 1))
	{
		if (flags[0] >= 0)
			flags[0]++;
		ft_write(1, "-", 1, flags);
		leint *= -1;
	}
	if (leint < 0 && flags[0] >= 0)
		if (flags[0] >= 0)
			flags[0]++;
	if (leint == 0 && flags[0] == 0)
		flags[2]++;
	return (parse2_int(leint, flags, len));
}
