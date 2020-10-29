/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 11:59:04 by gorban            #+#    #+#             */
/*   Updated: 2019/10/15 11:59:37 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt(int nb)
{
	long sqrt;

	if (nb % 2)
		sqrt = 1;
	else
		sqrt = 2;
	while (sqrt * sqrt < nb)
		sqrt += 2;
	if (sqrt * sqrt == nb)
		return (sqrt);
	return (0);
}
