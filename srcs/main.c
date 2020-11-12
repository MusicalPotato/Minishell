/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:43:32 by ijacquet          #+#    #+#             */
/*   Updated: 2020/11/10 17:29:24 by igor             ###   ########.fr       */
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
			while (c < data->cmd->arg_nbr)
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

int		ft_loop(t_data **data, char **envp)
{
	t_data	*tempo;
	int		r;

	if ((r = ft_line_reader(data)) <= 0)
		return (r);
	tempo = *data;
	while (tempo)
	{
		//ft_parse_env(tempo);
		if ((r = ft_parse_info(tempo)) <= 0)
			return (r);
		if ((r = ft_cmd_cmp(tempo->cmd, envp)) <= 0)
			return (r);
		tempo = tempo->next;
	}
//	ft_print_parse(*data);
	return (1);
}

int		main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = NULL;
	if (argc != 1)
	{
		write(2, "Wrong number of arguments\n", 26);
		return (0);
	}
	(void)argv;
	while (1)
	{
		if (!ft_loop(&data, envp))
		{
			ft_lstclear_line(&data);
			return (0);
		}
		ft_lstclear_line(&data);
	}
	return (1);
}
