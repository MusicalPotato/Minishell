/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:43:32 by ijacquet          #+#    #+#             */
/*   Updated: 2020/11/05 17:49:00 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_parse(t_line *line)
{
	int	a;
	int b;
	int	c;

	a = 1;
	while (line)
	{
		printf("\nLine n°%d : %s\n", a, line->line);
		b = 1;
		while (line->cmd)
		{
			printf("Commande n°%d : %s\n", b, line->cmd->cmd);
			c = 0;
			while (c <= line->cmd->msg_nbr)
			{
				printf("Message n°%d : %s\n", c + 1, line->cmd->msg[c]);
				c++;
			}
			line->cmd = line->cmd->next;
			b++;
		}
		line = line->next;
		a++;
	}
}

void	ft_loop(t_data data)
{
	t_line	*tempo;

	ft_line_reader(&data);
	tempo = data.line;
	while (tempo)
	{
		ft_parser(tempo);
		tempo = tempo->next;
	}
	ft_print_parse(data.line);
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
