/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reading.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:55:36 by ijacquet          #+#    #+#             */
/*   Updated: 2020/11/10 17:22:37 by igor             ###   ########.fr       */
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

int		ft_istext(int text, char c)
{
	if (!text && c == '\'')
		text = 1;	
	else if (text == 1 && c == '\'')
		text = 0;
	else if (!text && c == '"')
		text = 2;
	else if (text == 2 && c == '"')
		text = 0;
	return (text);
}

int		ft_ask_next(char **line)
{
	char	*text;
	
	text = NULL;
	if (!(get_next_line(1, &text)))
		return (exit_write("GNL Error\n", 0, 0));
	if (!(text = ft_memcat(text, "\n", ft_strlen(text), 1)))
		return (exit_write("malloc Error\n", 0, 0));
	if (!(*line = ft_memcat(*line, text, ft_strlen(*line), ft_strlen(text))))
		return (exit_write("malloc Error\n", 0, ft_freeturn(&text, 0)));
	free(text);
	return (1);
}

int		ft_check_text(int count, char **line)
{
	int		quote;
	int		size;

	quote = 0;
	size = 0;
	while (quote || !size)
	{
		if ((*line)[count + size] == 0)
			break ;
		while (((*line)[count + size] != ';' || quote) && (*line)[count + size] != 0)
		{
			while ((*line)[count + size] == '\\' && quote != 1)
			{
				size += 2;
				if (!(*line)[count + size])
				{
					ft_printf("> ");
					if (!(ft_ask_next(line)))
						return (-1);
				}
			}
			quote = ft_istext(quote, (*line)[count + size]);
			if ((*line)[count + size] != ';' || quote != 0)
				size++;
		}
		if (quote)
			ft_printf("%cquote> ", (quote - 1) * 100);
		if (quote)
			if (!(ft_ask_next(line)))
				return (-1);
	}
	return (size);
}

int		ft_line_saver(t_data **data, char *line)
{
	int		size;
	int		count;

	count = 0;
	while (line[count])
	{
		while (ft_is_space(line[count]) || line[count] == ';')
		{
			while (ft_is_space(line[count]))
				count++;
			if (line[count] == ';')
				count++;
			if (line[count] == ';')
			{
				ft_printf("parse error near `;;'\n");
				return (0);
			}
		}
		if ((size = ft_check_text(count, &line)) == -1)
			return (0);
		if (size)
			if (!(ft_lstadd_back_line(data,
				ft_lstnew_line(ft_strndup(line + count, size)))))
				return (0);
		count += size;
	}
	return (1);
}

int		ft_line_reader(t_data **data)
{
	char	*line;

	ft_printf("prompt > ");
	if (!(get_next_line(1, &line)))
		return (exit_write("GNL Error\n", 0, 0));
	if (!(line = ft_memcat(line, "\n", ft_strlen(line), 1)))
		return (exit_write("malloc Error\n", 0, 0));
	if (!(ft_line_saver(data, line)))
		return (ft_freeturn(&line, 0));
	free(line);
	return (1);
}
