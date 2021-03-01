/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:12:53 by gorban            #+#    #+#             */
/*   Updated: 2021/03/01 14:53:55 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_stradd_back(char **strs, char *new, int size)
{
	int		i;
	char	**newstrs;

	if (!(newstrs = malloc(sizeof(char *) * (size + 1))))
	{
		if (new)
			free(new);
		return (0);
	}
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
