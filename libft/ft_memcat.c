/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:35:13 by gorban            #+#    #+#             */
/*   Updated: 2020/10/29 15:09:43 by ijacquet         ###   ########.fr       */
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
	free(string);
	while (i < string_size + buf_size)
	{
		string2[i] = buf[i - string_size];
		i++;
	}
	string2[i] = '\0';
	return (string2);
}
