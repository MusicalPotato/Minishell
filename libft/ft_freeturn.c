/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freeturn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 15:10:12 by gorban            #+#    #+#             */
/*   Updated: 2021/03/01 14:51:32 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_freeturn(char **data, int value)
{
	if (data)
	{
		free(*data);
		*data = NULL;
	}
	return (value);
}
