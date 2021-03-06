/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 03:41:32 by igor              #+#    #+#             */
/*   Updated: 2021/03/06 14:24:20 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_countbs(char *str)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\\')
			n++;
		i++;
	}
	return (n);
}

int	var_to_value(char **str, int count, int s_var, char *val)
{
	char	*newstr;
	int		s_val;
	int		n;
	int		a;

	s_val = ft_strlen(val);
	n = ft_countbs(val);
	if (!(newstr = malloc(sizeof(char) * (ft_strlen(*str) - s_var + s_val + n))))
		return (exit_write("malloc Error\n", 0, 0));
	a = 0;
	while (a < count - 1)
	{
		newstr[a] = (*str)[a];
		a++;
	}
	n = 0;
	while (a < count + s_val - 1)
	{
		if (val[a - count + 1] == '\\')
		{
			newstr[a + n] = '\\';
			n++;
		}
		newstr[a + n] = val[a - count + 1];
		a++;
	}
	while ((*str)[a - s_val + s_var + 1])
	{
		newstr[a + n] = (*str)[a - s_val + s_var + 1];
		a++;
	}
	newstr[a + n] = 0;
	if (*str)
		free(*str);
	*str = newstr;
	return (1);
}

int	ft_parse_env(t_data *d, t_cmd *cmd)
{
	char	*var;
	char	*value;
	int		count;
	int		s_v;
	int		quote;
	int		to_free;

	count = 0;
	quote = 0;
	while (cmd->line[count])
	{
		s_v = 0;
		var = NULL;
		quote = ft_istext(quote, cmd->line[count]);
		if (quote != 1 && cmd->line[count] == '\\')
			count += 2;
		if (quote != 1 && cmd->line[count] == '$')
		{
			count++;
			if (cmd->line[count + s_v] != '?')
				while (ft_isalnum(cmd->line[count + s_v]) || cmd->line[count + s_v] == '_')
					s_v++;
			else
				s_v++;
			if (!(var = ft_memcat(var, cmd->line + count, 0, s_v)))
				return (exit_write("malloc Error\n", 0, -1));
			if (var[0])
			{
				to_free = 0;
				if (var[0] == '?')
				{
					if (!(value = ft_itoa(d->status)))
						return (exit_write("malloc Error\n", 0, -1));
					to_free = 1;
				}
				else
					value = ft_getenv(var, d->envp);
				if (!(var_to_value(&cmd->line, count, s_v, value)))
				{
					if (to_free)
						free(value);
					return (ft_freeturn(&var, -1));
				}
			if (to_free)
				free(value);
			count--;
			}
			free(var);
		}
		else
			count++;
	}
	return (0);
}
