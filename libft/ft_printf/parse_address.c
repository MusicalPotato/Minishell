/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 22:40:59 by gorban            #+#    #+#             */
/*   Updated: 2019/11/25 22:41:00 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse2_address(char *laddress, long flags[6], int bool, int len)
{
	if (bool == 0 && flags[0] >= 0)
	{
		ft_write(1, "0x", 2, flags);
		if (flags[0] > 0)
			flags[0] += 2;
		bool = 1;
	}
	while (flags[0]-- > len)
		ft_write(1, "0", 1, flags);
	flags[0]++;
	if (bool == 0)
		ft_write(1, "0x", 2, flags);
	if (*laddress != '0' || flags[0] != 0)
		ft_write(1, laddress, len - 2, flags);
	while (flags[3] == 1 && flags[2] > len && flags[2]-- > flags[0])
		ft_write(1, " ", 1, flags);
	return (ft_freeturn(&laddress, 1));
}

int	parse_address(char *laddress, long flags[6])
{
	int	len;
	int bool;

	if (!laddress)
		return (-1);
	bool = 0;
	if (flags[0] >= 0)
		flags[1] = 0;
	len = ft_strlen(laddress) + 2;
	if (flags[1] == 1 || flags[3] == 1)
	{
		if (flags[0] >= 0)
			flags[0] += 2;
		ft_write(1, "0x", 2, flags);
		bool = 1;
	}
	if (*laddress == '0' && flags[0] == 0)
		flags[2]++;
	while (flags[3] == 0 && flags[2] > len && flags[2]-- > flags[0])
		if (flags[1] == 0)
			ft_write(1, " ", 1, flags);
		else
			ft_write(1, "0", 1, flags);
	return (parse2_address(laddress, flags, bool, len));
}
