/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:41:50 by gorban            #+#    #+#             */
/*   Updated: 2019/10/16 21:46:48 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	char			*str;
	unsigned int	size;

	if (!(s) || !(f))
		return (0);
	str = (char *)s;
	size = ft_strlen(s);
	if (!(result = malloc(sizeof(char) * size + 1)))
		return (0);
	size = 0;
	while (s[size])
	{
		result[size] = f(size, s[size]);
		size++;
	}
	result[size] = 0;
	return (result);
}
