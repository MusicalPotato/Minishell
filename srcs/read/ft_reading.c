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

void	ft_change_cmd(t_hist **cur, char buf[BSIZE], char **str)
{
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		if ((*cur)->next)
			*cur = (*cur)->next;
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		if ((*cur)->prev)
			*cur = (*cur)->prev;
	free(*str);
	*str = ft_strdup((*cur)->line);
	return ;
}

int		ft_enter(t_data *data, char **str)
{
	int	ret;

	ft_printf("\n");
	if (data->index != 0)
	{
		if (!ft_lstadd_front_hist(&data->hist, ft_lstnew_hist(ft_strdup(*str))))
			return (ft_freeturn(str, exit_write("malloc Error\n", 0, -1)));
		if (!(*str = ft_memcat(*str, "\n", ft_strlen(*str), 1)))
			return (exit_write("malloc Error\n", 0, -1));
		write(data->fd, *str, ft_strlen(*str));
		if ((ret = ft_line_saver(data, str)))
			return (ft_freeturn(str, ret));
		free(*str);
		*str = NULL;
		data->index = 0;
		return (-42);
	}
	return (0);
}

int		ft_check_char(t_data *data, char buf[BSIZE], t_hist **cur, char **str)
{
	int	ret;

	if ((buf[0] == 10 && buf[1] == 0) || (buf[0] == 13 && buf[1] == 0))
	{
		if ((ret = ft_enter(data, str)))
			return (ret);
	}
	else if ((buf[0] == 27 && buf[1] == 91 && buf[2] == 65) ||
			(buf[0] == 27 && buf[1] == 91 && buf[2] == 66))
		ft_change_cmd(cur, buf, str);
	else if (buf[0] == 127 && buf[1] == 0)
	{
		if (data->index > 0)
			*str = ft_memcat(*str, 0, ft_strlen(*str) - 1, 0);
	}
	else if (buf[0] == 4 && buf[1] == 0)
	{
		if (data->index == 0)
			ft_exit(g_data->cmd, exit_write("\nexit\n", 0, 0));
	}
	else
		*str = ft_memcat(*str, buf, ft_strlen(*str), ft_strlen(buf));
	return (0);
}

int		ft_display_char(t_data *data, char buf[BSIZE], t_hist **cur)
{
	static char	*str;
	int			ret;

	if ((ret = ft_check_char(data, buf, cur, &str)))
		return (ret);
	data->index = ft_strlen(str);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 0, ft_outc);
	tputs(tgetstr("cd", NULL), 0, ft_outc);
	ft_printf("prompt > ");
	if (data->index != 0 && str)
		ft_printf("%s", str);
	return (0);
}

int		ft_line_reader(t_data *data)
{
	char	buf[BSIZE];
	int		ret;
	t_hist	*cur;

	if (tcsetattr(0, 0, &(data->termios)) == -1)
		return (-1);
	data->inexec = 0;
	cur = data->hist;
	ft_printf("prompt > ");
	while (1)
	{
		ft_bzero(buf, BSIZE);
		if (read(STDIN_FILENO, buf, BSIZE) < 0)
			return (-1);
		if ((ret = ft_display_char(data, buf, &cur)) == -42)
			break ;
		if (ret != 0)
			return (ret);
	}
	data->inexec = 1;
	if (tcsetattr(0, 0, &(data->termios_backup)) == -1)
		return (-1);
	return (0);
}
