/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:43:32 by ijacquet          #+#    #+#             */
/*   Updated: 2021/01/29 12:53:04 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_loop(t_data **data, char ***envp)
{
	t_data	*tempo;
	int		r;

	(void)envp;
	if ((r = ft_line_reader(data)) <= 0)
		return (r);
	tempo = *data;
	while (tempo)
	{
		ft_parse_env(tempo, envp);
		if ((r = ft_parse_info(tempo)) <= 0)
			return (r);
		if ((r = ft_setup_exec(tempo->cmd, envp)) <= 0)
			return (r);
		tempo = tempo->next;
	}
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
	signal(SIGINT,handler);
	signal(SIGQUIT,handler);
	while (1)
	{
		if (!ft_loop(&data, &envp))
		{
			ft_lstclear_line(&data);
			ft_envpclear(&envp);
			return (0);
		}
		ft_lstclear_line(&data);
	}
	return (1);
}
