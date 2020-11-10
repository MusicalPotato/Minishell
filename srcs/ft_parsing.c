/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:02:19 by ijacquet          #+#    #+#             */
/*   Updated: 2020/11/10 13:52:02 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_msg_recup(char *line, int count, t_cmd *cmd)
{
	int quote;

	while (cmd->next)
		cmd = cmd->next;
	cmd->arg_nbr = 0;
	quote = 0;
	cmd->arg = NULL;
	while (line[count] != '\n' && line[count] != '\0' && line[count] != '|')
	{
		while (ft_is_space(line[count]))
			count++;
		if (line[count] == '\n' || line[count] == '\0' || line[count] == '|')
			break ;
		if (line[count] != '\n')
			if (!(cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0), cmd->arg_nbr++)))
				return (exit_write("malloc Error\n", 0, -1));
		while (quote || (line[count] != '\n' && line[count] != ' ' && line[count] != '|' && line[count] != '\0' && line[count] != '\t'))
		{
			if (line[count] == '\\' && (quote == 0 || (quote == 2 && (line[count + 1] == '"' || line[count + 1] == '\\'))))
			{
				count++;
				if (line[count] != '\n')
					if (!(cmd->arg[cmd->arg_nbr - 1] = ft_memcat(cmd->arg[cmd->arg_nbr - 1], line + count, ft_strlen(cmd->arg[cmd->arg_nbr - 1]), 1)))
						return (exit_write("malloc Error\n", 0, -1));
				count++;
			}
			else if ((line[count] == '"' && quote != 1) || (line[count] == '\'' && quote != 2))
			{
				quote = ft_istext(quote, line[count]);
				if ((quote != 1 && line[count] == '"') || (quote != 2 && line[count] == '\''))
					count++;
			}
			else
			{
				if (!(cmd->arg[cmd->arg_nbr - 1] = ft_memcat(cmd->arg[cmd->arg_nbr - 1], line + count, ft_strlen(cmd->arg[cmd->arg_nbr - 1]), 1)))
					return (exit_write("malloc Error\n", 0, -1));
				count++;
			}
		}
	}
	return (count);
}

int		ft_cmd_recup(char *line, int count, char **cmd)
{
	int quote;

	quote = 0;
	while (line[count] != '\0' && (quote || (line[count] != '\n' && line[count] != ' ' && line[count] != '|' && line[count] != '\t')))
	{
		if (line[count] == '\\' && (quote == 0 || (quote == 2 && (line[count + 1] == '"' || line[count + 1] == '\\'))))
		{
			count++;
			if (line[count] != '\n')
				if (!(*cmd = ft_memcat(*cmd, line + count, ft_strlen(*cmd), 1)))
					return (exit_write("malloc Error\n", 0, -1));
			count++;
		}
		else if ((line[count] == '"' && quote != 1) || (line[count] == '\'' && quote != 2))
		{
			quote = ft_istext(quote, line[count]);
			if ((quote != 1 && line[count] == '"') || (quote != 2 && line[count] == '\''))
				count++;
		}
		else
		{
			if (!(*cmd = ft_memcat(*cmd, line + count, ft_strlen(*cmd), 1)))
				return (exit_write("malloc Error\n", 0, -1));
			count++;
		}
	}
	return (count);
}

int		ft_pipe_check(t_data *d, int count, int x)
{
	if (x)
	{
		if (d->line[count] == '|')
		{
			count++;
			while (ft_is_space(d->line[count]))
				count++;
		}
		if (d->line[count] == '|')
			return (exit_write("parse error near `|'\n", 0, -1));
	}
	else if (d->line[count] == '|')
		return (exit_write("parse error near `|'\n", 0, -1));
	return (count);
}

int		ft_parser(t_data *d)
{
	int		count;
	char	*cmd;
	int		x;

	count = 0;
	x = 0;
	while (d->line[count] == '|' || !x)
	{
		cmd = malloc(1);
		*cmd = 0;
		if ((count = ft_pipe_check(d, count, x)) < 0)
			return (ft_freeturn(&cmd, -1));
		if ((count = ft_cmd_recup(d->line, count, &cmd)) < 0)
			return (0);
		if (!(ft_lstadd_back_cmd(&(d->cmd),
			ft_lstnew_cmd(ft_strdup(cmd)))))
			return (ft_freeturn(&cmd, 0));
		free(cmd);
		if (d->line[count] == ' ' || d->line[count] == '\t')
			if ((count = ft_msg_recup(d->line, count, d->cmd)) < 0)
				return (0);
		x++;
	}
	return (1);
}
