/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reading.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:55:36 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/30 12:59:45 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_is_space(char line)
{
	if (line == ' ' || line == '\t' || line == '\n'
	|| line == '\v' || line == '\f' || line == '\r')
		return (1);
	return (0);
}

int		ft_line_count(t_data *data, char *line)
{
	int	i;
	int	size;

	i = 1;
	while (*line)
	{
		while (ft_is_space(*line) || *line == ';')
		{
			while (ft_is_space(*line))
				line++;
			if (*line == ';')
				line++;
			if (*line == ';')
				return (0);
		}
		size = 0;
		while (line[size] != ';' && line[size] != 0)
			size++;
		if (size)
			if (!(ft_lstadd_back_line(&(data->line),
				ft_lstnew_line(ft_strndup(line, size)))))
				return (0);
		line += size;
	}
	return (i);
}

int		ft_line_reader(t_data *data)
{
	char	*line;

	ft_printf("prompt > ");
	get_next_line(1, &line);
	return (1);
}
