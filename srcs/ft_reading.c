/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reading.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:55:36 by ijacquet          #+#    #+#             */
/*   Updated: 2020/11/02 12:53:40 by ijacquet         ###   ########.fr       */
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

int		ft_check_text(int count, char **line)
{
	int		quote;
	int		size;
	char	*text;

	quote = 0;
	size = 0;
	while (quote || !size)
		{
			if ((*line)[count + size] == 0)
				break ;
			while (((*line)[count + size] != ';' || quote) && (*line)[count + size] != 0)
			{
				quote = ft_istext(quote, (*line)[count + size]);
				size++;
			}
			if (quote == 1)
				ft_printf("quote> ");
			else if (quote == 2)
				ft_printf("dquote> ");
			if (quote)
			{
				get_next_line(1, &text);
				*line = ft_memcat(*line, "\n", ft_strlen(*line), 1);
				*line = ft_memcat(*line, text, ft_strlen(*line), ft_strlen(text));
			}
		}
	return (size);
}

int		ft_line_saver(t_data *data, char *line)
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
				return (0);
		}
		size = ft_check_text(count, &line);
		if (size)
			if (!(ft_lstadd_back_line(&(data->line),
				ft_lstnew_line(ft_strndup(line + count, size)))))
				return (0);
		count += size;
	}
	return (1);
}

int		ft_line_reader(t_data *data)
{
	char	*line;

	ft_printf("prompt > ");
	get_next_line(1, &line);
	ft_line_saver(data, line);
	return (1);
}
