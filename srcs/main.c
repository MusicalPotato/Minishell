/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:43:32 by ijacquet          #+#    #+#             */
/*   Updated: 2021/02/19 15:06:29 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_loop(t_data **data, char ***envp, int *status)
{
	t_data	*tempo;
	int		r;

	(void)envp;
	if ((r = ft_line_reader(data)))
		return ((*status = r));
	tempo = *data;
	while (tempo)
	{
		if (ft_parse_env(tempo, envp, status) < 0)
			return (-1);
		if ((r = ft_parse_info(tempo)))
			return ((*status = r));
		if (tempo->cmd->arg_nbr)
			ft_putenv(ft_envformat("_", tempo->cmd->arg[tempo->cmd->arg_nbr - 1]), envp, 1);
		else
			ft_putenv(ft_envformat("_", tempo->cmd->name), envp, 1);
		if ((r = ft_setup_exec(tempo->cmd, envp, status)))
			return (r);
		tempo = tempo->next;
	}
	return (1);
}

int		ft_loop2(t_data **data, char ***envp, int *status, char *argv)
{
	t_data	*tempo;
	int		r;
	char	*str;

	(void)envp;
	str = ft_strdup(argv);
	if (!(str = ft_memcat(str, "\n", ft_strlen(str), 1)))
		return (exit_write("malloc Error\n", 0, ft_freeturn(&str, -1)));
	if ((r = ft_line_saver(data, &str)))
		return (ft_freeturn(&str, (*status = r)));
	free(str);
	tempo = *data;
	while (tempo)
	{
		errno = 0;
		if (ft_parse_env(tempo, envp, status) < 0)
			return (-1);
		if ((r = ft_parse_info(tempo)))
			return ((*status = r));
		if (tempo->cmd->arg_nbr)
			ft_putenv(ft_envformat("_", tempo->cmd->arg[tempo->cmd->arg_nbr - 1]), envp, 1);
		else
			ft_putenv(ft_envformat("_", tempo->cmd->name), envp, 1);
		if ((r = ft_setup_exec(tempo->cmd, envp, status)))
			return (r);
		tempo = tempo->next;
	}
	return (1);
}

int		main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		status;

	data = NULL;
	status = 0;
	if (argc != 1)
	{
		if (argv[1][0] == '-' && argv[1][1] == 'c' && argc == 3)
		{
			(void)argv;
			signal(SIGINT,handler);
			signal(SIGQUIT,handler);
			if (ft_loop2(&data, &envp, &status, argv[2]) < 0)
			{
				ft_lstclear_line(&data);
				ft_envpclear(&envp);
				return (0);
			}
//			ft_lstclear_line(&data);
		}
		else
			write(2, "Wrong number of arguments\n", 26);
		return (status);
	}
	else
	{
		(void)argv;
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
		while (1)
		{
			if (ft_loop(&data, &envp, &status) < 0)
			{
				ft_lstclear_line(&data);
				ft_envpclear(&envp);
				return (0);
			}
			ft_lstclear_line(&data);
		}
	}
	return (1);
}
