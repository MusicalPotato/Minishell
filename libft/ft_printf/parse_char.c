/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 16:09:50 by gorban            #+#    #+#             */
/*   Updated: 2019/11/25 16:09:52 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parse_char(char lechar, long flags[6])
{
	int size;

	size = 1;
	while (flags[3] == 0 && flags[2] > size)
	{
		if (flags[1] == 0)
			ft_write(1, " ", 1, flags);
		else
			ft_write(1, "0", 1, flags);
		size++;
	}
	ft_write(1, &lechar, 1, flags);
	while (flags[3] == 1 && flags[2] > size)
	{
		ft_write(1, " ", 1, flags);
		size++;
	}
	return (1);
}
