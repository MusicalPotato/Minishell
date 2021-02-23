/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reading.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:55:36 by ijacquet          #+#    #+#             */
/*   Updated: 2021/02/23 12:12:03 by igor             ###   ########.fr       */
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
	int		r;
	char	*text;

	text = NULL;
	if ((r = get_next_line(1, &text)) < 0)
		return (exit_write("GNL Error\n", 0, -1));
	else if (r == 0)
		return (ft_freeturn(line, -1));
	if (!(text = ft_memcat(text, "\n", ft_strlen(text), 1)))
		return (exit_write("malloc Error\n", 0, -1));
	if (!(*line = ft_memcat(*line, text, ft_strlen(*line), ft_strlen(text))))
		return (exit_write("malloc Error\n", 0, ft_freeturn(&text, -1)));
	free(text);
	return (1);
}

int		ft_pipe_chev_check(int count, char **line, int i)
{
	while (ft_is_space((*line)[count]))
		count++;
	if ((*line)[count] == ';' && i > 0)
	{
		count++;
		while (ft_is_space((*line)[count]))
			count++;
		if ((*line)[count] == '|')
			return (exit_write("minishell: syntax error near unexpected token `|'\n", 0, 2));
	}
	if (((*line)[count] == '<' || (*line)[count] == '>' || (*line)[count] == '|') && i > 0)
	{
		count++;
		while (ft_is_space((*line)[count]))
			count++;
		if ((*line)[count] == ';')
			return (exit_write("minishell: syntax error near unexpected token `;'\n", 0, 2));
	}
	if (((*line)[count] == '<' || (*line)[count] == '>') && i == 0)
	{
		if ((*line)[count] == '>')
			count++;
		count++;
		while (ft_is_space((*line)[count]))
			count++;
		if ((*line)[count] == ';')
			return (exit_write("minishell: syntax error near unexpected token `;'\n", 0, 2));
	}
	return (0);
}

int		ft_check_text(int count, char **line)
{
	int		quote;
	int		size;
	int 	pipe;

	quote = 0;
	size = 0;
	pipe = 0;
	while (quote || pipe || !size)
	{
		if ((*line)[count + size] == 0)
			break ;
		while (((*line)[count + size] != ';' || quote || pipe) && (*line)[count + size] != 0)
		{
			if (quote == 0 && ft_pipe_chev_check(count + size, line, count + size))
				return (-2);
			if (!ft_is_space((*line)[count + size]))
				pipe = 0;
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
			if ((*line)[count + size] == '|')
				pipe = 1;
			quote = ft_istext(quote, (*line)[count + size]);
			if ((*line)[count + size] != ';' || quote != 0)
				size++;
		}
		if (quote)
			ft_printf("%cquote> ", (quote - 1) * 100);
		if (pipe)
			ft_printf("pipe> ");
		if (quote || pipe)
			if (!(ft_ask_next(line)))
				return (-1);
	}
	return (size);
}

int		ft_line_saver(t_data **data, char **line)
{
	int		size;
	int		count;
	int		fcmd;
	int		end;

	count = 0;
	fcmd = 0;
	if ((ft_pipe_chev_check(count, line, 0)))
		return (2);
	while ((*line)[count])
	{
		end = 0;
		while (ft_is_space((*line)[count]) || (*line)[count] == ';')
		{
			while (ft_is_space((*line)[count]))
				count++;
			if ((*line)[count] == ';' && !fcmd)
				return (exit_write("minishell: syntax error near unexpected token `;'\n", 0, 2));
			if ((*line)[count] == ';')
			{
				if (!end && (end = 1))
					count++;
				else
					return (exit_write("minishell: syntax error near unexpected token `;'\n", 0, 2));
			}
		}
		fcmd = 1;
		if ((size = ft_check_text(count, line)) < 0)
		{
			if (size == -2)
				return (2);
			return (-1);
		}
		if (size)
			if (!(ft_lstadd_back_line(data,
				ft_lstnew_line(ft_strndup(*line + count, size)))))
				return (exit_write("malloc Error\n", 0, -1));
		count += size;
	}
	return (0);
}

int		ft_line_reader(t_data **data)
{
	char	*line;
	int		r;

	inexec = 0;
	ft_printf("prompt > ");
	if ((r = get_next_line(1, &line)) < 0)
		return (exit_write("GNL Error\n", 0, -1));
	else if (r == 0)
		return (exit_write("\nExit\n", 0, ft_freeturn(&line, -1)));
	if (!(line = ft_memcat(line, "\n", ft_strlen(line), 1)))
		return (exit_write("malloc Error\n", 0, -1));
	if ((r = ft_line_saver(data, &line)))
		return (ft_freeturn(&line, r));
	free(line);
	inexec = 1;
	return (0);
}
