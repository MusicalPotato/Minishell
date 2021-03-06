/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:42:48 by gorban            #+#    #+#             */
/*   Updated: 2021/03/01 14:52:05 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(long long nbr)
{
	int x;

	x = 0;
	if (nbr >= 10)
		x = ft_intlen(nbr / 10);
	else if (nbr < 0)
		x = ft_intlen(nbr * -1);
	return (x + 1);
}
