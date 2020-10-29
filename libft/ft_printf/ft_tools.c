/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:31:42 by gorban            #+#    #+#             */
/*   Updated: 2019/11/21 17:06:34 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_write_nbr(int fd, long nbr, long flags[6])
{
	long	nb;
	char	c;

	nb = nbr;
	if (nb < 0)
	{
		nb = -nb;
		ft_write(fd, "-", 1, flags);
	}
	if (nb > 9)
		ft_write_nbr(fd, nb / 10, flags);
	c = (char)(nb % 10 + '0');
	ft_write(fd, &c, 1, flags);
}

void	ft_write(int fd, char *c, int size, long flags[6])
{
	if (!c)
		return ;
	write(fd, c, size);
	flags[5] += size;
}
