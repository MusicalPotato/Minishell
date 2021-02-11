/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:35:13 by gorban            #+#    #+#             */
/*   Updated: 2021/02/11 11:40:44 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memcat(char *string, char *buf, int string_size, int buf_size)
{
	int		i;
	char	*string2;

	if (!(string2 = malloc(sizeof(char) * (string_size + buf_size + 1))))
	{
		free(string);
		return (NULL);
	}
	i = 0;
	while (i < string_size)
	{
		string2[i] = string[i];
		i++;
	}
	while (i < string_size + buf_size)
	{
		string2[i] = buf[i - string_size];
		i++;
	}
	free(string);
	string2[i] = '\0';
	return (string2);
}
