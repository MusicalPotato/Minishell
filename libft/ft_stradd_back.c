/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:12:53 by gorban            #+#    #+#             */
/*   Updated: 2020/02/03 12:12:56 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_stradd_back(char **strs, char *new, int size)
{
	int 	i;
	char	**newstrs;

	if (!new)
		return (0);
	if (!(newstrs = malloc(sizeof(char *) * (size + 1))))
		return (0);
	i = 0;
	while (i < size)
	{
		newstrs[i] = strs[i];
		i++;
	}
	newstrs[i] = new;
	if (strs)
		free(strs);
	return (newstrs);
}
