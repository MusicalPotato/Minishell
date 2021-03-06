/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line_saver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 00:23:05 by igor              #+#    #+#             */
/*   Updated: 2021/03/16 00:25:50 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int			ft_line_saver(t_data *data, char **line)
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
			if (!(ft_lstadd_back_cmd(&(data->cmd),
				ft_lstnew_cmd(ft_strndup(*line + count, size)))))
				return (exit_write("malloc Error\n", 0, -1));
		count += size;
	}
	return (0);
}
