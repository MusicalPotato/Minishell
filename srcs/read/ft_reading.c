/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reading.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:55:36 by ijacquet          #+#    #+#             */
/*   Updated: 2021/03/05 13:27:12 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_outc(int c)
{
	return ((int)write(STDIN_FILENO, &c, 1));
}

int			ft_line_reader(t_data *data)
{
	int		ret;
	int		index;
	char	buf[BSIZE];
	char	*string;
	t_hist	*cur;

    if (tcsetattr(0, 0, &(data->termios)) == -1)
        return (-1);
	data->inexec = 0;
	cur = data->hist;
	string = NULL;
	index = 0;
	ft_printf("prompt > ");
	while (1)
	{
		ft_bzero(buf, BSIZE);
		if (read(STDIN_FILENO, buf, BSIZE) < 0)
			return (-1);
		if (ENTER)
		{
			write(STDOUT_FILENO, "\n", 1);
			if (string && string[0] != 0)
			{
				ft_lstadd_front_hist(&data->hist, ft_lstnew_hist(ft_strdup(string)));
				if (!(string = ft_memcat(string, "\n", ft_strlen(string), 1)))
					return (exit_write("malloc Error\n", 0, -1));
				write(data->fd, string, ft_strlen(string));
				if ((ret = ft_line_saver(data, &string)))
					return (ft_freeturn(&string, ret));
				free(string);
				string = NULL;
				break ;
			}
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
			ft_printf("prompt > ");
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
			ft_printf("prompt > ");
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
				tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
				tputs(tgetstr("cd", NULL), 0, ft_outc);
				ft_printf("prompt > ");
				string = ft_memcat(string, 0, ft_strlen(string) - 1, 0);
				write(STDOUT_FILENO, string, ft_strlen(string));
				index = ft_strlen(string);
			}
		}
		else
		{
			string = ft_memcat(string, buf, ft_strlen(string), ft_strlen(buf));
			index = ft_strlen(string);
			write(STDOUT_FILENO, buf, ft_strlen(buf));
		}
	}
	data->inexec = 1;
	if (tcsetattr(0, 0, &(data->termios_backup)) == -1)
        return (-1);
	return (0);
}
