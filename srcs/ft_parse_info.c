/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:02:19 by ijacquet          #+#    #+#             */
/*   Updated: 2021/02/04 14:20:15 by tkleynts         ###   ########.fr       */
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
	while (ft_is_space(line[count]))
		count++;
	if ((line[0] == '>' || line[0] == '<') && line[count] == '<')
		return (exit_write("syntax error near unexpected token ", "'<'", -1));
	if ((line[0] == '>' || line[0] == '<') && line[count] == '>')
		return (exit_write("syntax error near unexpected token ", "'>'", -1));
	while (line[count] != '\n' && line[count] != '\0')
	{
		while (ft_is_space(line[count]))
			count++;
		if (line[count] == '\n' || line[count] == '\0')
			break ;
		if (line[count] != '\n' && line[count] != '<' && line[count] != '>' && line[count] != '|')
			if (!(cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0), cmd->arg_nbr++)))
				return (exit_write("malloc Error\n", 0, 0));
		while (quote || (line[count] != '\n' && line[count] != ' ' && line[count] != '\0' && line[count] != '\t'))
		{
			if (line[count] == '\\' && (quote == 0 || (quote == 2 && (line[count + 1] == '"' || line[count + 1] == '\\'))))
			{
				count++;
				if (line[count] != '\n')
					if (!(cmd->arg[cmd->arg_nbr - 1] = ft_memcat(cmd->arg[cmd->arg_nbr - 1], line + count, ft_strlen(cmd->arg[cmd->arg_nbr - 1]), 1)))
						return (exit_write("malloc Error\n", 0, 0));
				count++;
			}
			else if ((line[count] == '"' && quote != 1) || (line[count] == '\'' && quote != 2))
			{
				quote = ft_istext(quote, line[count]);
				if ((quote != 1 && line[count] == '"') || (quote != 2 && line[count] == '\''))
					count++;
			}
			else if ((line[count] == '>' || line[count] == '<') && !quote)
			{
				if (!(cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0), cmd->arg_nbr++)))
					return (exit_write("malloc Error\n", 0, 0));
				if (!(cmd->arg[cmd->arg_nbr - 1] = ft_memcat(cmd->arg[cmd->arg_nbr - 1], line + count, ft_strlen(cmd->arg[cmd->arg_nbr - 1]), 1)))
					return (exit_write("malloc Error\n", 0, 0));
				count++;
				if (line[count - 1] == '>' && line[count] == '>')
				{
					if (!(cmd->arg[cmd->arg_nbr - 1] = ft_memcat(cmd->arg[cmd->arg_nbr - 1], line + count, ft_strlen(cmd->arg[cmd->arg_nbr - 1]), 1)))
						return (exit_write("malloc Error\n", 0, 0));
					count++;
				}
				if (line[count] == '<')
					return (exit_write("'<<' not supported by minishell\n", 0, -1));
				while (ft_is_space(line[count]))
					count++;
				if (line[count] == '<')
					return (exit_write("syntax error near unexpected token ", "'<'", -1));
				else if (line[count] == '>')
					return (exit_write("syntax error near unexpected token ", "'>'", -1));
				if (line[count] && line[count] != ' ' && line[count] != '\n')
					if (!(cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0), cmd->arg_nbr++)))
						return (exit_write("malloc Error\n", 0, 0));
			}
			else if ((line[count] == '|') && !quote)
			{
				if (!(cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0), cmd->arg_nbr++)))
					return (exit_write("malloc Error\n", 0, 0));
				if (!(cmd->arg[cmd->arg_nbr - 1] = ft_memcat(cmd->arg[cmd->arg_nbr - 1], line + count, ft_strlen(cmd->arg[cmd->arg_nbr - 1]), 1)))
					return (exit_write("malloc Error\n", 0, 0));
				count++;
				while (ft_is_space(line[count]))
					count++;
				if (line[count] == '|')
					return (exit_write("syntax error near unexpected token ", "'|'", -1));
				if (line[count] && line[count] != ' ' && line[count] != '\n')
					if (!(cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0), cmd->arg_nbr++)))
						return (exit_write("malloc Error\n", 0, 0));
			}
			else
			{
				if (!(cmd->arg[cmd->arg_nbr - 1] = ft_memcat(cmd->arg[cmd->arg_nbr - 1], line + count, ft_strlen(cmd->arg[cmd->arg_nbr - 1]), 1)))
					return (exit_write("malloc Error\n", 0, 0));
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
	if (line[0] == '|')
		exit_write("syntax error near unexpected token `|'\n", 0, -2);
	if (line[0] == ';')
		exit_write("syntax error near unexpected token `;'\n", 0, -2);
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
		else if ((line[count] == '>' || line[count] == '<') && !quote)
		{
			if (count)
				return (count);
			if (!(*cmd = ft_memcat(*cmd, line + count, ft_strlen(*cmd), 1)))
				return (exit_write("malloc Error\n", 0, -1));
			count++;
			if (line[count - 1] == '<' && line[count] == '<')
				return (exit_write("syntax error near unexpected token ", "'<'", -2));
			if (line[count - 1] == '>' && line[count] == '<')
				return (exit_write("syntax error near unexpected token ", "'<'", -2));
			if (line[count - 1] == '>' && line[count] == '>')
			{
				if (!(*cmd = ft_memcat(*cmd, line + count, ft_strlen(*cmd), 1)))
					return (exit_write("malloc Error\n", 0, -1));
				count++;
				if (line[count] == '<')
					return (exit_write("syntax error near unexpected token ", "'<'", -2));
				if (line[count] == '>')
					return (exit_write("syntax error near unexpected token ", "'>'", -2));
			}
			return (count);
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

int		ft_parse_info(t_data *d)
{
	int		count;
	char	*cmd;
	int		x;

	count = 0;
	x = -1;
	while (!++x)
	{
		cmd = malloc(1);
		*cmd = 0;
		if ((count = ft_cmd_recup(d->line, count, &cmd)) < 0)
			return (count + 1);
		if (count == 0)
			return (-1);
		if (!(ft_lstadd_back_cmd(&(d->cmd),
			ft_lstnew_cmd(ft_strdup(cmd)))))
			return (ft_freeturn(&cmd, 0));
		free(cmd);
		if (d->line[count] == ' ' || d->line[count] == '\t' || d->line[count] == '|' || d->line[count - 1] == '>' || d->line[count - 1] == '<' || d->line[count] == '>' || d->line[count] == '<')
			if ((count = ft_msg_recup(d->line, count, d->cmd)) <= 0)
				return (count);
	}
	return (1);
}
