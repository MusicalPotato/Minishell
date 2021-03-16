/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:43:32 by ijacquet          #+#    #+#             */
/*   Updated: 2021/03/06 14:34:02 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_loop(t_data *data)
{
	t_cmd	*cur;
	int		r;

	if ((r = ft_line_reader(data)))
		return ((data->status = r));
	cur = data->cmd;
	while (cur)
	{
		if (ft_parse_env(data, cur) < 0)
			return (-1);
		if ((r = ft_parse_info(cur)))
			return ((data->status = r));
		ft_putenv(ft_envformat("_", cur->argv[cur->argc]), &(data->envp), 1);
		if ((r = ft_setup_exec(data, cur)))
			return (r);
		cur = cur->next;
	}
	return (1);
}

int		ft_init_term(char **envp)
{
	int		ret;
	char	*term_type;

	term_type = ft_getenv("TERM", envp);
	if (term_type == NULL)
		return (exit_write("TERM must be set (see 'env').\n", 0, 0));
	ret = tgetent(NULL, term_type);
	if (ret == -1)
		return (exit_write(
			"Could not access to the termcap database..\n", 0, 0));
	else if (ret == 0)
	{
		return (exit_write("Terminal type is not defined in termcap \
				database (or have too few informations).\n", 0, 0));
	}
	return (1);
}

int		ft_claim_history(void)
{
	char	*line;
	int		ret;

	line = NULL;
	g_data->fd = open(".history", O_APPEND | O_CREAT | O_RDWR, S_IRWXU);
	if (g_data->fd < 0)
		return (0);
	if (!(g_data->hist = ft_lstnew_hist(NULL)))
		return (0);
	while ((ret = get_next_line(g_data->fd, &line)) > 0)
	{
		if (!(ft_lstadd_front_hist(&(g_data->hist), ft_lstnew_hist(line))))
			return (0);
	}
	free(line);
	if (ret == -1)
		return (exit_write("claim : GNL Error\n", 0, 0));
	return (1);
}

int		ft_setup(int argc, char **argv, char **envp)
{
	char	*str;

	str = NULL;
	if (argc > 1)
		return (exit_write("Wrong number of arguments\n", 0, 0));
	if (!(g_data = ft_lstnew_data(envp)))
		return (0);
	if (!(str = getcwd(0, 0))
	|| !(ft_putenv(ft_envformat("PWD", str), &(g_data->envp), 1))
	|| !(ft_putshlvl(ft_getenv("SHLVL", g_data->envp), &(g_data->envp), 1))
	|| !(str = ft_memcat(str, argv[0], 0, ft_strlen(argv[0])))
	|| !(ft_putenv(ft_envformat("_", str), &(g_data->envp), 1)))
	{
		ft_freeturn(&str, 0);
		ft_lstclear_data(&(g_data));
		return (exit_write("malloc Error\n", 0, 0));
	}
	free(str);
	if (!(ft_claim_history())
	|| !ft_init_term(g_data->envp))
	{
		ft_lstclear_data(&(g_data));
		return (0);
	}
	return (1);
}

int		main(int argc, char **argv, char **envp)
{
	int		status;

	g_data = NULL;
	if (!ft_setup(argc, argv, envp))
		return (-1);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	while (1)
	{
		if (ft_loop(g_data) < 0)
		{
			status = g_data->status;
			ft_lstclear_data(&g_data);
			return (status);
		}
		ft_lstclear_cmd(&(g_data->cmd));
	}
	return (1);
}
