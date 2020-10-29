/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:14:32 by gorban            #+#    #+#             */
/*   Updated: 2019/11/25 20:14:34 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_hex(char *lhexa, long flags[6])
{
	int	len;
	int pre;

	if (!lhexa)
		return (-1);
	if (flags[0] >= 0)
		flags[1] = 0;
	len = ft_strlen(lhexa);
	if (*lhexa == '0' && flags[0] == 0)
		flags[2]++;
	while (flags[3] == 0 && flags[2] > len && flags[2]-- > flags[0])
		if (flags[1] == 0)
			ft_write(1, " ", 1, flags);
		else
			ft_write(1, "0", 1, flags);
	pre = flags[0];
	while (pre-- > len)
		ft_write(1, "0", 1, flags);
	if (*lhexa != '0' || flags[0] != 0)
		ft_write(1, lhexa, len, flags);
	while (flags[3] == 1 && flags[2] > len && flags[2]-- > flags[0])
		ft_write(1, " ", 1, flags);
	return (ft_freeturn(&lhexa, 1));
}
