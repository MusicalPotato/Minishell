/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:43:32 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/29 15:39:37 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_loop(t_data data)
{
	ft_cmd_reader(&data.cmd);
	printf("ligne lue = '%s'\n", data.cmd.line);
}

int		main()
{
	t_data data;
	
	while (1)
	{
		ft_loop(data);
	}
	return (0);
}
