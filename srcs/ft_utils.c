/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:47:22 by ijacquet          #+#    #+#             */
/*   Updated: 2020/11/05 14:15:45 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(const char *s1, int size)
{
	char	*copy;
	int		n;

	if (!(copy = malloc(sizeof(char) * size + 1)))
		return (0);
	n = 0;
	while (n < size)
	{
		copy[n] = s1[n];
		n++;
	}
	copy[n] = 0;
	return (copy);
}

int		exit_write(char *msg, char *bonus, int value)
{
	write(2, msg, ft_strlen(msg));
	if (bonus)
	{
		write(2, bonus, ft_strlen(bonus));
		write(2, "\n", 1);
	}
	return (value);
}

int		free_all(char ***data, int ret)
{
	int	i;

	i = 0;
	if (*data)
	{
		while ((*data)[i])
		{
			ft_freeturn(&((*data)[i]), 1);
			i++;
		}
		free(*data);
	}
	*data = NULL;
	return (ret);
}
