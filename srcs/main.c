/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:43:32 by ijacquet          #+#    #+#             */
/*   Updated: 2020/11/06 14:56:20 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_parse(t_data *data)
{
	int	a;
	int b;
	int	c;

	a = 1;
	while (data)
	{
		printf("\nLine n°%d : %s\n", a, data->line);
		b = 1;
		while (data->cmd)
		{
			printf("Commande n°%d : %s\n", b, data->cmd->name);
			c = 0;
			while (c <= data->cmd->arg_nbr)
			{
				printf("Message n°%d : %s\n", c + 1, data->cmd->arg[c]);
				c++;
			}
			data->cmd = data->cmd->next;
			b++;
		}
		data = data->next;
		a++;
	}
}

void	ft_loop(t_data *data)
{
	t_data	*tempo;

	ft_line_reader(data);
	tempo = data;
	while (tempo)
	{
		ft_parser(tempo);
		tempo = tempo->next;
	}

	ft_print_parse(&data);
}

int		ft_initialize(t_data *data)
{
	data = NULL;
	return (1);
}

int		main(int argc, char **argv)
{
	t_data	data;
	if (argc != 1)
	{
		write(2, "Wrong number of arguments\n", 26);
		return (0);
	}
	(void)argv;
	ft_initialize(&data);
	while (1)
	{
		ft_loop(&data);
		ft_lstclear_line(&(data));
	}
	return (0);
}
