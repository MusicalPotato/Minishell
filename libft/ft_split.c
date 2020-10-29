/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:30:51 by gorban            #+#    #+#             */
/*   Updated: 2019/10/18 18:08:23 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_complet_tab(const char *str, int min, int max)
{
	char	*tab;
	int		size;
	int		x;

	x = 0;
	size = max - min;
	if (!(tab = malloc(sizeof(char) * (size + 1))))
		return (0);
	while (min < max)
	{
		tab[x] = str[min];
		min++;
		x++;
	}
	tab[x] = 0;
	return (tab);
}

static void	ft_settab(char const *s, char c, int a, char **tab)
{
	int	x;
	int	t;

	x = 0;
	t = 0;
	while (s[++a])
		if (s[a] == c || !(s[a + 1]))
		{
			if (!(s[a + 1]) && !(s[a] == c))
				tab[t++] = ft_complet_tab(s, a - x, a + 1);
			else if (x > 0)
				tab[t++] = ft_complet_tab(s, a - x, a);
			if (t != 0 && !(tab[t - 1]))
			{
				while (t - 1)
					free(tab[--t - 1]);
				return ;
			}
			x = 0;
		}
		else
			x++;
	tab[t] = 0;
}

static int	splitlen(char const *s, char c)
{
	int	a;
	int	x;
	int	size;

	a = 0;
	x = 0;
	size = 0;
	while (s[a])
	{
		if (s[a] == c || !(s[a + 1]))
		{
			if (!(s[a + 1] && s[a] == c))
				x++;
			if (x > 0)
				size++;
			x = 0;
		}
		else
			x++;
		a++;
	}
	return (size);
}

char		**ft_split(char const *s, char c)
{
	int		size;
	char	**tab;
	int		a;

	if (!s)
		return (0);
	size = splitlen(s, c);
	if (!(tab = malloc(sizeof(char *) * (size + 1))))
		return (0);
	a = -1;
	ft_settab(s, c, a, tab);
	return (tab);
}
