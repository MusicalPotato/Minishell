/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 03:41:32 by igor              #+#    #+#             */
/*   Updated: 2021/01/25 14:41:25 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	var_to_value(char **str, int count, int s_var, char *val)
{
	char *newstr;
	int s_val;
	int a;

	s_val = ft_strlen(val);
	if (!(newstr = malloc(sizeof(char) * (ft_strlen(*str) - s_var + s_val))))
		return (exit_write("malloc Error\n", 0, 0));
	a = 0;
	while (a < count - 1)
	{
		newstr[a] = (*str)[a];
		a++;
	}
	while (a < count + s_val - 1)
	{
		newstr[a] = val[a - count + 1];
		a++;
	}
	while ((*str)[a - s_val + s_var + 1])
	{
		newstr[a] = (*str)[a - s_val + s_var + 1];
		a++;
	}
	newstr[a] = 0;
	free(*str);
	*str = newstr;
	return (1);
}

int	ft_parse_env(t_data *d, char ***envp)
{
	char	*var;
	char	*value;
	int		count;
	int 	s_v;
	int		quote;

	count = 0;
	quote = 0;
	while (d->line[count])
	{
		s_v = 0;
		var = NULL;
		quote = ft_istext(quote, d->line[count]);
		if (quote != 1 && d->line[count] == '$')
		{
			count++;
			if (d->line[count + s_v] != '?')
				while (ft_isalnum(d->line[count + s_v]) || d->line[count + s_v] == '_')
					s_v++;
			else
				s_v++;
			if (!(var = ft_memcat(var, d->line + count, 0, s_v)))
				return (exit_write("malloc Error\n", 0, 0));
			if (var[0])
			{
				if (var[0] == '?')
				{
					if (!(value = ft_itoa(errno)))
						return (0);
				}
				else
					value = ft_getenv(var, *envp);
				if (!(var_to_value(&d->line, count, s_v, value)))
					return (ft_freeturn(&var, 0));
			}
			free(var);
		}
		else
			count++;
	}
	return (1);
}
