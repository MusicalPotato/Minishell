/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:43:32 by ijacquet          #+#    #+#             */
/*   Updated: 2020/11/02 13:02:55 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_loop(t_data data)
{
	ft_line_reader(&data);
	while (data.line)
	{
		printf("ligne lue = -%s-\n", data.line->line);
		data.line = data.line->next;
	}
}

int		ft_initialize(t_data *data)
{
	data = NULL;
	return (1);
}

int		main(int argc, char **argv)
{
	t_data data;

	if (argc != 1)
	{
		write(2, "Wrong number of arguments\n", 26);
		return (0);
	}
	(void)argv;
	ft_initialize(&data);
	while (1)
	{
		ft_loop(data);
		ft_lstclear_line(&(data.line));
	}
	return (0);
}
