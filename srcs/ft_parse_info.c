/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:02:19 by ijacquet          #+#    #+#             */
/*   Updated: 2021/02/19 12:10:14 by igor             ###   ########.fr       */
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
		return (exit_write("syntax error near unexpected token ", "'<'", -2));
	if ((line[0] == '>' || line[0] == '<') && line[count] == '>' && line[count + 1] == '>')
		return (exit_write("syntax error near unexpected token ", "'>>'", -2));
	else if ((line[0] == '>' || line[0] == '<') && line[count] == '>')
		return (exit_write("syntax error near unexpected token ", "'>'", -2));
	while (line[count] != '\n' && line[count] != '\0')
	{
		while (ft_is_space(line[count]))
			count++;
		if (line[count] == '\n' || line[count] == '\0')
			break ;
		if (line[count] != '\n' && line[count] != '<' && line[count] != '>' && line[count] != '|')
			if (!(cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0), cmd->arg_nbr++)))
				return (exit_write("malloc Error\n", 0, -1));
		while (quote || (line[count] != '\n' && line[count] != ' ' && line[count] != '\0' && line[count] != '\t'))
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
			else if ((line[count] == '>' || line[count] == '<') && !quote)
			{
				if (!(cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0), cmd->arg_nbr++)))
					return (exit_write("malloc Error\n", 0, -1));
				if (!(cmd->arg[cmd->arg_nbr - 1] = ft_memcat(cmd->arg[cmd->arg_nbr - 1], line + count, ft_strlen(cmd->arg[cmd->arg_nbr - 1]), 1)))
					return (exit_write("malloc Error\n", 0, -1));
				count++;
				if (line[count - 1] == '>' && line[count] == '>')
				{
					if (!(cmd->arg[cmd->arg_nbr - 1] = ft_memcat(cmd->arg[cmd->arg_nbr - 1], line + count, ft_strlen(cmd->arg[cmd->arg_nbr - 1]), 1)))
						return (exit_write("malloc Error\n", 0, -1));
					count++;
				}
				if (line[count] == '<')
					return (exit_write("'<<' not supported by minishell\n", 0, -2));
				while (ft_is_space(line[count]))
					count++;
				if (line[count] == '<')
					return (exit_write("syntax error near unexpected token ", "'<'", -2));
				else if (line[count] == '>' && line[count + 1] == '>')
					return (exit_write("syntax error near unexpected token ", "'>>'", -2));
				else if (line[count] == '>')
					return (exit_write("minishell: syntax error near unexpected token ", "'>'", -2));
				if (line[count] && line[count] != ' ' && line[count] != '\n')
					if (!(cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0), cmd->arg_nbr++)))
						return (exit_write("malloc Error\n", 0, -1));
			}
			else if ((line[count] == '|') && !quote)
			{
				if (!(cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0), cmd->arg_nbr++)))
					return (exit_write("malloc Error\n", 0, -1));
				if (!(cmd->arg[cmd->arg_nbr - 1] = ft_memcat(cmd->arg[cmd->arg_nbr - 1], line + count, ft_strlen(cmd->arg[cmd->arg_nbr - 1]), 1)))
					return (exit_write("malloc Error\n", 0, -1));
				count++;
				while (ft_is_space(line[count]))
					count++;
				if (line[count] == '|')
					return (exit_write("minishell: syntax error near unexpected token ", "'|'", -2));
				if (line[count] && line[count] != ' ' && line[count] != '\n')
					if (!(cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0), cmd->arg_nbr++)))
						return (exit_write("malloc Error\n", 0, -1));
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
	if (line[0] == '|')
		exit_write("minishell: syntax error near unexpected token `|'\n", 0, -2);
	if (line[0] == ';')
		exit_write("minishell: syntax error near unexpected token `;'\n", 0, -2);
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
				return (exit_write("minishell: syntax error near unexpected token ", "'<'", -2));
			if (line[count - 1] == '>' && line[count] == '<')
				return (exit_write("minishell: syntax error near unexpected token ", "'<'", -2));
			if (line[count - 1] == '>' && line[count] == '>')
			{
				if (!(*cmd = ft_memcat(*cmd, line + count, ft_strlen(*cmd), 1)))
					return (exit_write("malloc Error\n", 0, -1));
				count++;
				if (line[count] == '<')
					return (exit_write("minishell: syntax error near unexpected token ", "'<'", -2));
				if (line[count] == '>')
					return (exit_write("minishell: syntax error near unexpected token ", "'>'", -2));
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
	int		ret;
	char	*cmd;

	ret = 0;
	cmd = malloc(1);
	*cmd = 0;
	if ((ret = ft_cmd_recup(d->line, ret, &cmd)) < -1)
		return (ft_abs(ret));
	if (ret == -1)
		return (-1);
	if (!(ft_lstadd_back_cmd(&(d->cmd),
		ft_lstnew_cmd(ft_strdup(cmd)))))
		return (ft_freeturn(&cmd, -1));
	free(cmd);
	if (d->line[ret] == ' ' || d->line[ret] == '\t' || d->line[ret] == '|' || d->line[ret - 1] == '>' || d->line[ret - 1] == '<' || d->line[ret] == '>' || d->line[ret] == '<')
	{	
		if ((ret = ft_msg_recup(d->line, ret, d->cmd)) < -1)
			return (ft_abs(ret));
		if (ret == -1)
			return (-1);
	}
	return (0);
}
