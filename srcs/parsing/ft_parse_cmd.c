/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:02:19 by ijacquet          #+#    #+#             */
/*   Updated: 2021/03/06 14:24:29 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_parse_error_check(t_cmd *cmd)
{
	if ((cmd->argv[0][0] == '>' || cmd->argv[0][0] == '<') && cmd->argc == 0)
		return (exit_write(SYNERR, "`newline'", 2));
	if ((cmd->argv[0][0] == '>' || cmd->argv[0][0] == '<') &&
		cmd->argv[1][0] == '|')
		return (exit_write(SYNERR, "`|'", 2));
	if (cmd->argc == 0)
		return (0);
	if (cmd->argv[cmd->argc][0] == '>' ||
			cmd->argv[cmd->argc][0] == '<')
		return (exit_write(SYNERR, "`newline'", 2));
	return (0);
}

int		ft_cmd_check_1(char *line, int count, char **cmd, int i)
{
	if (i == 0)
	{
		if (line[0] == '|')
			return (exit_write(SYNERR, "`|'", -2));
		if (line[0] == ';')
			return (exit_write(SYNERR, "`;'", -2));
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
		return (exit_write(SYNERR, "`<'", -2));
	if (line[count - 1] == '>' && line[count] == '<')
		return (exit_write(SYNERR, "`<'", -2));
	if (line[count - 1] == '>' && line[count] == '>')
	{
		if (!(*cmd = ft_memcat(*cmd, line + count, ft_strlen(*cmd), 1)))
			return (exit_write("malloc Error\n", 0, -1));
		count++;
		if (line[count] == '<')
			return (exit_write(SYNERR, "`<'", -2));
		if (line[count] == '>')
			return (exit_write(SYNERR, "`>'", -2));
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
			count = ft_cmd_check_1(line, count, cmd, 1);
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
			count = ft_cmd_check_1(line, count, cmd, 2);
		if (count < 0)
			return (count);
	}
	return (count);
}

int		ft_parse_info(t_cmd *cur)
{
	int		count;
	char	*cmd;

	count = 0;
	cmd = malloc(1);
	*cmd = 0;
	if ((count = ft_cmd_recup(cur->line, count, &cmd, 0)) < -1)
		return (ft_abs(count));
	if (count == -1)
		return (-1);
	cur->argv = malloc(sizeof(char *) * 1);
	cur->argv[0] = ft_strdup(cmd);
	free(cmd);
	if (cur->line[count] == ' ' || cur->line[count] == '\t' || cur->line[count]
	== '|' || cur->line[count - 1] == '>' || cur->line[count - 1] == '<' ||
	cur->line[count] == '>' || cur->line[count] == '<')
	{
		if ((count = ft_msg_recup(cur, count, cur->line)) < -1)
			return (ft_abs(count));
		if (count == -1)
			return (-1);
	}
	return (ft_parse_error_check(cur));
}
