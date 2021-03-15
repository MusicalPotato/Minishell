/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 00:27:31 by igor              #+#    #+#             */
/*   Updated: 2021/03/16 00:29:21 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_outc(int c)
{
	return ((int)write(STDIN_FILENO, &c, 1));
}

static int	ft_pipe_chev_check_0(int count, char **line, int i)
{
	while (ft_is_space((*line)[count]))
		count++;
	if ((*line)[count] == ';' && i > 0)
	{
		count++;
		while (ft_is_space((*line)[count]))
			count++;
		if ((*line)[count] == '|')
			return (exit_write(SYNERR, "`|'", -2));
	}
	if (((*line)[count] == '<' || (*line)[count] == '>' ||
		(*line)[count] == '|') && i > 0)
	{
		count++;
		while (ft_is_space((*line)[count]))
			count++;
		if ((*line)[count] == ';')
			return (exit_write(SYNERR, "`;'", -2));
	}
	return (count);
}

int			ft_pipe_chev_check(int count, char **line, int i)
{
	if ((count = ft_pipe_chev_check_0(count, line, i)) == -2)
		return (2);
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
