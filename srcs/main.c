/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:43:32 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/30 11:53:51 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_loop(t_data data)
{
	ft_cmd_reader(&data);
	printf("ligne lue = '%s'\n", data.line->line);
}

int		ft_initialize(t_data *data)
{
	data = NULL;
	return (1);
}

int		main()
{
	t_data data;

	ft_initialize(&data);
	while (1)
	{
		ft_loop(data);
	}
	return (0);
}
