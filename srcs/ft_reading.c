/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reading.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:55:36 by ijacquet          #+#    #+#             */
/*   Updated: 2021/03/02 14:35:13 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_is_space(char line)
{
	if (line == ' ' || line == '\t' || line == '\n'
	|| line == '\v' || line == '\f' || line == '\r')
		return (1);
	return (0);
}

int			ft_istext(int text, char c)
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

int			ft_pipe_chev_check(int count, char **line, int i)
{
	while (ft_is_space((*line)[count]))
		count++;
	if ((*line)[count] == ';' && i > 0)
	{
		count++;
		while (ft_is_space((*line)[count]))
			count++;
		if ((*line)[count] == '|')
			return (exit_write(SYNERR, "`|'", 2));
	}
	if (((*line)[count] == '<' || (*line)[count] == '>' || (*line)[count] == '|') && i > 0)
	{
		count++;
		while (ft_is_space((*line)[count]))
			count++;
		if ((*line)[count] == ';')
			return (exit_write(SYNERR, "`;'", 2));
	}
	if (((*line)[count] == '<' || (*line)[count] == '>') && i == 0)
	{
		if ((*line)[count] == '>')
			count++;
		count++;
		while (ft_is_space((*line)[count]))
			count++;
		if ((*line)[count] == ';')
			return (exit_write(SYNERR, "`;'", 2));
	}
	return (0);
}

static int	ft_reach_end(char **line, int count, int size, int quo_pi[2])
{
	while (((*line)[count + size] != ';' || quo_pi[0]
			|| quo_pi[1]) && (*line)[count + size] != 0)
	{
		if (quo_pi[0] == 0 && ft_pipe_chev_check(count + size,
											line, count + size))
			return (-2);
		if (!ft_is_space((*line)[count + size]))
			quo_pi[1] = 0;
		while ((*line)[count + size] == '\\' && quo_pi[0] != 1)
		{
			size += 2;
			if (!(*line)[count + size])
				return (exit_write(MLERR, 0, -2));
		}
		if ((*line)[count + size] == '|')
			quo_pi[1] = 1;
		quo_pi[0] = ft_istext(quo_pi[0], (*line)[count + size]);
		if ((*line)[count + size] != ';' || quo_pi[0] != 0)
			size++;
	}
	return (size);
}

int			ft_check_text(int count, char **line)
{
	int		quo_pi[2];
	int		size;

	quo_pi[0] = 0;
	quo_pi[1] = 0;
	size = 0;
	while (quo_pi[0] || quo_pi[1] || !size)
	{
		if ((*line)[count + size] == 0)
			break ;
		if ((size = ft_reach_end(line, count, size, quo_pi)) < 0)
			return (size);
		if (quo_pi[0] || quo_pi[1])
			return (exit_write(MLERR, 0, -2));
	}
	return (size);
}

static int	ft_skipspace(char **line, int count, int fcmd)
{
	int	end;

	end = 0;
	while (ft_is_space((*line)[count]) || (*line)[count] == ';')
	{
		while (ft_is_space((*line)[count]))
			count++;
		if ((*line)[count] == ';' && !fcmd)
			return (exit_write(SYNERR, "`;'", -1));
		if ((*line)[count] == ';')
		{
			if (!end && (end = 1))
				count++;
			else
				return (exit_write(SYNERR, "`;'", -1));
		}
	}
	return (count);
}

int			ft_line_saver(t_data **data, char **line)
{
	int		size;
	int		count;
	int		fcmd;

	count = 0;
	fcmd = 0;
	if ((ft_pipe_chev_check(count, line, 0)))
		return (2);
	while ((*line)[count])
	{
		if ((count = ft_skipspace(line, count, fcmd)) < 0)
			return (2);
		fcmd = 1;
		if ((size = ft_check_text(count, line)) < 1)
			return (ft_abs(size));
		else if (size < 0)
			return (size);
		if (size)
			if (!(ft_lstadd_back_data(data,
				ft_lstnew_data(ft_strndup(*line + count, size)))))
				return (exit_write("malloc Error\n", 0, -1));
		count += size;
	}
	return (0);
}
/*
int			ft_line_reader(t_data **data)
{
	char	*line;
	int		r;

	g_inexec = 0;
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
	g_inexec = 1;
	return (0);
}*/

int			ft_init_term(char ***envp)
{
    int		ret;
    char	*term_type;

	term_type = ft_getenv("TERM", *envp);
    if (term_type == NULL)
		return (exit_write("TERM must be set (see 'env').\n", 0, 0));
    ret = tgetent(NULL, term_type);
    if (ret == -1)
		return (exit_write("Could not access to the termcap database..\n", 0, 0));
    else if (ret == 0)
		return (exit_write("Terminal type is not defined in termcap database (or have too few informations).\n", 0, 0));
    return (1);
}

int			ft_outc(int c)
{
	return ((int)write(STDIN_FILENO, &c, 1));
}

int			ft_line_reader(t_data **data, char ***envp, t_hist **hist)
{
	char	buf[BSIZE];
	char	*string;
	int		fd;
	int		index;
	t_hist	*cur;
	struct	termios termios;

	if (!ft_init_term(envp))
		return (-1);
	if (tcgetattr(0, &termios) == -1)
        return (-1);
	termios.c_lflag &= ~(ICANON);
	termios.c_lflag &= ~(ECHO);
    if (tcsetattr(0, 0, &termios) == -1)
        return (-1);
	fd = open("history", O_APPEND | O_CREAT | O_RDWR);
	cur = *hist;
	string = NULL;
	index = 0;
	ft_printf("prompt > ");
	while (1)
	{
		ft_bzero(buf, BSIZE);
		read(STDIN_FILENO, buf, BSIZE);
		if (ENTER)
		{
			write(STDOUT_FILENO, "\n", 1);
			if (string && string[0] != 0)
			{
				ft_lstadd_front_hist(hist, ft_lstnew_hist(ft_strdup(string)));
				if (!(string = ft_memcat(string, "\n", ft_strlen(string), 1)))
					return (exit_write("malloc Error\n", 0, -1));
				write(fd, string, ft_strlen(string));
				if ((fd = ft_line_saver(data, &string)))
					return (ft_freeturn(&string, fd));
				free(string);
				string = NULL;
				cur = *hist;
				return (0);
			}
			else
				ft_printf("prompt > ");
		}
		else if (HAUT)
		{
			if (cur->next)
				cur = cur->next;
			tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
			tputs(tgetstr("cd", NULL), 0, ft_outc);
			free(string);
			string = ft_strdup(cur->line);
			index = ft_strlen(string);
			write(STDOUT_FILENO, cur->line, ft_strlen(cur->line));
		}
		else if (BAS)
		{
			tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
			tputs(tgetstr("cd", NULL), 0, ft_outc);
			if (cur->prev)
				cur = cur->prev;
			free(string);
			string = NULL;
			if (cur->line)
			{
				string = ft_strdup(cur->line);
				write(STDOUT_FILENO, cur->line, ft_strlen(cur->line));
			}
			index = ft_strlen(string);
		}
		else if (SUPP)
		{
			if (index > 0)
			{
				write(STDOUT_FILENO, "\b", 1);
				tputs(tgoto(tgetstr("ec", NULL), 0, 0), 0, ft_outc);
				string = ft_memcat(string, 0, ft_strlen(string) - 1, 0);
				index += -1;
			}
		}
		else
		{
			string = ft_memcat(string, buf, ft_strlen(string), ft_strlen(buf));
			index += 1;
			write(STDOUT_FILENO, buf, ft_strlen(buf));
		}
	}
	return (0);
}
