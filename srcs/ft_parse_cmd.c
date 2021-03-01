/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:02:19 by ijacquet          #+#    #+#             */
/*   Updated: 2021/03/01 13:35:45 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_parse_error_check(t_cmd *cmd)
{
	if ((cmd->name[0] == '>' || cmd->name[0] == '<') && cmd->arg_nbr == 0)
		return (exit_write(
		"minishell: syntax error near unexpected token `newline'\n", 0, 2));
	if ((cmd->name[0] == '>' || cmd->name[0] == '<') && cmd->arg[0][0] == '|')
		return (exit_write(
		"minishell: syntax error near unexpected token `|'\n", 0, 2));
	if (cmd->arg_nbr == 0)
		return (0);
	if (cmd->arg[cmd->arg_nbr - 1][0] == '>' ||
		cmd->arg[cmd->arg_nbr - 1][0] == '<')
		return (exit_write(
		"minishell: syntax error near unexpected token `newline'\n", 0, 2));
	return (0);
}

int		ft_cmd_check_1(char *line, int count, char **cmd, int i)
{
	if (i == 0)
	{
		if (line[0] == '|')
			return (exit_write("minishell: syntax error near unexpected token `|'\n", 0, -2));
		if (line[0] == ';')
			return (exit_write("minishell: syntax error near unexpected token `;'\n", 0, -2));
	}
	else if (i == 1)
	{
		count++;
		if (line[count] != '\n')
			if (!(*cmd = ft_memcat(*cmd, line + count, ft_strlen(*cmd), 1)))
				return (exit_write("malloc Error\n", 0, -1));
		count++;
	}
	else if (i == 2)
	{
		if (!(*cmd = ft_memcat(*cmd, line + count, ft_strlen(*cmd), 1)))
			return (exit_write("malloc Error\n", 0, -1));
		count++;
	}
	return (count);
}

int		ft_cmd_check_2(char *line, int count, char **cmd)
{
	if (count)
		return (count);
	if (!(*cmd = ft_memcat(*cmd, line + count, ft_strlen(*cmd), 1)))
		return (exit_write("malloc Error\n", 0, -1));
	count++;
	if (line[count - 1] == '<' && line[count] == '<')
		return (exit_write(
			"minishell: syntax error near unexpected token ", "`<'", -2));
	if (line[count - 1] == '>' && line[count] == '<')
		return (exit_write(
			"minishell: syntax error near unexpected token ", "`<'", -2));
	if (line[count - 1] == '>' && line[count] == '>')
	{
		if (!(*cmd = ft_memcat(*cmd, line + count, ft_strlen(*cmd), 1)))
			return (exit_write("malloc Error\n", 0, -1));
		count++;
		if (line[count] == '<')
			return (exit_write(
				"minishell: syntax error near unexpected token ", "`<'", -2));
		if (line[count] == '>')
			return (exit_write(
				"minishell: syntax error near unexpected token ", "`>'", -2));
	}
	return (count);
}

int		ft_cmd_recup(char *line, int count, char **cmd, int quote)
{
	if ((count = ft_cmd_check_1(line, count, cmd, 0)) < 0)
		return (count);
	while (line[count] != '\0' && (quote || (line[count] != '\n' && line[count]
					!= ' ' && line[count] != '|' && line[count] != '\t')))
	{
		if (line[count] == '\\' && (quote == 0 || (quote == 2 && (line[count
					+ 1] == '"' || line[count + 1] == '\\'))))
		{
			if ((count = ft_cmd_check_1(line, count, cmd, 1)) < 0)
				return (count);
		}
		else if ((line[count] == '"' && quote != 1) || (line[count] == '\''
					&& quote != 2))
		{
			quote = ft_istext(quote, line[count]);
			if ((quote != 1 && line[count] == '"') || (quote != 2 &&
					line[count] == '\''))
				count++;
		}
		else if ((line[count] == '>' || line[count] == '<') && !quote)
			return (ft_cmd_check_2(line, count, cmd));
		else
			if ((count = ft_cmd_check_1(line, count, cmd, 2)) < 0)
				return (count);
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
	if ((ret = ft_cmd_recup(d->line, ret, &cmd, 0)) < -1)
		return (ft_abs(ret));
	if (ret == -1)
		return (-1);
	if (!(ft_lstadd_back_cmd(&(d->cmd), ft_lstnew_cmd(ft_strdup(cmd)))))
		return (ft_freeturn(&cmd, -1));
	free(cmd);
	if (d->line[ret] == ' ' || d->line[ret] == '\t' || d->line[ret] == '|' ||
	d->line[ret - 1] == '>' || d->line[ret - 1] == '<' || d->line[ret] == '>'
	|| d->line[ret] == '<')
	{	
		if ((ret = ft_msg_recup(d->line, ret, d->cmd)) < -1)
			return (ft_abs(ret));
		if (ret == -1)
			return (-1);
	}
	return (ft_parse_error_check(d->cmd));
}
