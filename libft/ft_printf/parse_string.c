/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 16:39:34 by gorban            #+#    #+#             */
/*   Updated: 2019/11/25 16:39:36 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_string(char *lastring, long flags[6])
{
	int size;
	int len;

	if (!lastring)
		lastring = "(null)";
	len = ft_strlen(lastring);
	if (flags[0] >= 0 && len > flags[0])
		len = flags[0];
	size = len;
	while (flags[3] == 0 && flags[2] > size)
	{
		if (flags[1] == 0)
			ft_write(1, " ", 1, flags);
		else
			ft_write(1, "0", 1, flags);
		size++;
	}
	ft_write(1, lastring, len, flags);
	while (flags[3] == 1 && flags[2] > size)
	{
		ft_write(1, " ", 1, flags);
		size++;
	}
	return (1);
}
