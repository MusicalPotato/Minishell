/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:38:59 by igor              #+#    #+#             */
/*   Updated: 2021/03/02 14:12:52 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_msg_check_1(char *line, int count, int i, int *quote)
{
	if (i == 0)
	{
		while (ft_is_space(line[count]))
			count++;
		if ((line[0] == '>' || line[0] == '<') && line[count] == '<')
			return (exit_write(SYNERR, "`<'", -2));
		if ((line[0] == '>' || line[0] == '<') && line[count] == '>' &&
				line[count + 1] == '>')
			return (exit_write(SYNERR, "`>>'", -2));
		else if ((line[0] == '>' || line[0] == '<') && line[count] == '>')
			return (exit_write(SYNERR, "`>'", -2));
	}
	else if (i == 1)
	{
		*quote = ft_istext(*quote, line[count]);
		if ((*quote != 1 && line[count] == '"') || (*quote != 2 &&
				line[count] == '\''))
			count++;
	}
	return (count);
}

int		ft_msg_check_2(char *line, int count, t_cmd *cmd, int i)
{
	if (i == 0)
	{
		if (line[++count] != '\n')
			if (!(cmd->arg[cmd->arg_nbr - 1] = ft_memcat(cmd->arg[cmd->arg_nbr
			- 1], line + count, ft_strlen(cmd->arg[cmd->arg_nbr - 1]), 1)))
				return (exit_write("malloc Error\n", 0, -1));
		count++;
		return (count);
	}
	if (!(cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0), cmd->arg_nbr++)))
		return (exit_write("malloc Error\n", 0, -1));
	if (!(cmd->arg[cmd->arg_nbr - 1] = ft_memcat(cmd->arg[cmd->arg_nbr - 1],
	line + count, ft_strlen(cmd->arg[cmd->arg_nbr - 1]), 1)))
		return (exit_write("malloc Error\n", 0, -1));
	count++;
	while (ft_is_space(line[count]))
		count++;
	if (line[count] == '|')
		return (exit_write(SYNERR, "`|'", -2));
	if (line[count] && line[count] != ' ' && line[count] != '\n')
		if (!(cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0),
			cmd->arg_nbr++)))
			return (exit_write("malloc Error\n", 0, -1));
	return (count);
}

int		ft_msg_check_3(char *line, int count, t_cmd *cmd)
{
	if (!(cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0), cmd->arg_nbr++)))
		return (exit_write("malloc Error\n", 0, -1));
	if (!(cmd->arg[cmd->arg_nbr - 1] = ft_memcat(cmd->arg[cmd->arg_nbr - 1],
				line + count++, ft_strlen(cmd->arg[cmd->arg_nbr - 1]), 1)))
		return (exit_write("malloc Error\n", 0, -1));
	if (line[count - 1] == '>' && line[count] == '>')
		if (!(cmd->arg[cmd->arg_nbr - 1] = ft_memcat(cmd->arg[cmd->arg_nbr - 1]
		, line + count, ft_strlen(cmd->arg[cmd->arg_nbr - 1]), 1)) || !count++)
			return (exit_write("malloc Error\n", 0, -1));
	if (line[count] == '<')
		return (exit_write("`<<' not supported by minishell\n", 0, -2));
	while (ft_is_space(line[count]))
		count++;
	if (line[count] == '<')
		return (exit_write(SYNERR, "`<'", -2));
	else if (line[count] == '>' && line[count + 1] == '>')
		return (exit_write(SYNERR, "`>>'", -2));
	else if (line[count] == '>')
		return (exit_write(SYNERR, "`>'", -2));
	if ((line[count] && line[count] != ' ' && line[count] != '\n') &&
		(!(cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0), cmd->arg_nbr++))))
		return (exit_write("malloc Error\n", 0, -1));
	return (count);
}

int		ft_msg_check(char *line, int count, int *quote, t_cmd *cmd)
{
	if (line[count] == '\\' && (*quote == 0 || (*quote == 2 && (line[count + 1]
				== '"' || line[count + 1] == '\\' || line[count + 1] == '$'))))
		count = ft_msg_check_2(line, count, cmd, 0);
	else if ((line[count] == '"' && *quote != 1) || (line[count] == '\''
				&& *quote != 2))
		count = ft_msg_check_1(line, count, 1, quote);
	else if ((line[count] == '>' || line[count] == '<') && !*quote)
		count = ft_msg_check_3(line, count, cmd);
	else if ((line[count] == '|') && !*quote)
		count = ft_msg_check_2(line, count, cmd, 1);
	else if (!(cmd->arg[cmd->arg_nbr - 1] =
		ft_memcat(cmd->arg[cmd->arg_nbr - 1],
		line + count, ft_strlen(cmd->arg[cmd->arg_nbr - 1]), 1)) || !count++)
		return (exit_write("malloc Error\n", 0, -1));
	return (count);
}

int		ft_msg_recup(char *line, int count, t_cmd *cmd)
{
	int quote;

	cmd->arg_nbr = 0;
	quote = 0;
	cmd->arg = NULL;
	if ((count = ft_msg_check_1(line, count, 0, &quote)) < 0)
		return (count);
	while (line[count] != '\n' && line[count] != '\0')
	{
		while (ft_is_space(line[count]))
			count++;
		if (line[count] == '\n' || line[count] == '\0')
			break ;
		if (line[count] != '\n' && line[count] != '<' && line[count] != '>'
					&& line[count] != '|')
			if (!(cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0),
					cmd->arg_nbr++)))
				return (exit_write("malloc Error\n", 0, -1));
		while (quote || (line[count] != '\n' && line[count] != ' ' &&
					line[count] != '\0' && line[count] != '\t'))
			if ((count = ft_msg_check(line, count, &quote, cmd)) < 0)
				return (count);
	}
	return (count);
}
