/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:02:19 by ijacquet          #+#    #+#             */
/*   Updated: 2020/11/05 16:18:02 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
int		ft_cmd_cmp(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "echo", 5))
		ft_echo(cmd);
	else if (ft_strncmp(cmd->cmd, "cd", 3))
		ft_cd(cmd);
	else if (ft_strncmp(cmd->cmd, "pwd", 4))
		ft_pwd(cmd);
	else if (ft_strncmp(cmd->cmd, "export", 7))
		ft_export(cmd);
	else if (ft_strncmp(cmd->cmd, "unset", 6))
		ft_unset(cmd);
	else if (ft_strncmp(cmd->cmd, "env", 4))
		ft_env(cmd);
	else if (ft_strncmp(cmd->cmd, "exit", 5))
		ft_exit(cmd);
	else
		ft_error();
}
*/
int		ft_msg_recup(char **line, int count, t_cmd *cmd)
{
	int quote;

	cmd->msg_nbr = -1;
	quote = 0;
	cmd->msg = malloc(0);
	while ((*line)[count] != '\n' && (*line)[count] != '\0' && (*line)[count] != '|')
	{
		while (ft_is_space((*line)[count]))
			count++;
		if ((*line)[count] == '\n' || (*line)[count] == '\0')
			break ;
		if ((*line)[count] != '\n')
		{
			cmd->msg_nbr++;
			cmd->msg = ft_stradd_back(cmd->msg, ft_strdup(0), cmd->msg_nbr);
		}
		while (quote || ((*line)[count] != '\n' && (*line)[count] != ' ' && (*line)[count] != '|' && (*line)[count] != '\0' && (*line)[count] != '\t'))
		{
			if ((*line)[count] == '\\' && (quote == 0 || (quote == 2 && ((*line)[count + 1] == '"' || (*line)[count + 1] == '\\'))))
			{
				count++;
				if ((*line)[count] != '\n')
					cmd->msg[cmd->msg_nbr] = ft_memcat(cmd->msg[cmd->msg_nbr], (*line) + count, ft_strlen(cmd->msg[cmd->msg_nbr]), 1);
				count++;
			}
			else if (((*line)[count] == '"' && quote != 1) || ((*line)[count] == '\'' && quote != 2))
			{
				quote = ft_istext(quote, (*line)[count]);
				if ((quote != 1 && (*line)[count] == '"') || (quote != 2 && (*line)[count] == '\''))
					count++;
			}
			else
			{
				cmd->msg[cmd->msg_nbr] = ft_memcat(cmd->msg[cmd->msg_nbr], (*line) + count, ft_strlen(cmd->msg[cmd->msg_nbr]), 1);
				count++;
			}
		}
		printf("Message n°%d : %s\n", cmd->msg_nbr + 1, cmd->msg[cmd->msg_nbr]);
	}
	return (count);
}

int		ft_cmd_recup(char **line, int count, t_cmd *cmd)
{
	int quote;

	quote = 0;
	while ((*line)[count] != '\0' && (quote || ((*line)[count] != '\n' && (*line)[count] != ' ' && (*line)[count] != '|' && (*line)[count] != '\t')))
	{
		if ((*line)[count] == '\\' && (quote == 0 || (quote == 2 && ((*line)[count + 1] == '"' || (*line)[count + 1] == '\\'))))
		{
			count++;
			if ((*line)[count] != '\n')
				cmd->cmd = ft_memcat(cmd->cmd, (*line) + count, ft_strlen(cmd->cmd), 1);
			count++;
		}
		else if (((*line)[count] == '"' && quote != 1) || ((*line)[count] == '\'' && quote != 2))
		{
			quote = ft_istext(quote, (*line)[count]);
			if ((quote != 1 && (*line)[count] == '"') || (quote != 2 && (*line)[count] == '\''))
				count++;
		}
		else
		{
			cmd->cmd = ft_memcat(cmd->cmd, (*line) + count, ft_strlen(cmd->cmd), 1);
			count++;
		}
	}
	return (count);
}

int		ft_pipe_check(t_line *line, int count)
{
	if (line->line[count] == '|' && line->cmd_nbr)
		count++;
	else if (line->line[count] == '|')
	{
		ft_printf("va te faire enculer\n");
		return (-1);
	}
	return (count);
}

int		ft_parser(t_line *line)
{
	int count;

	count = 0;
	if (!(line->cmd = malloc(sizeof(t_cmd))))
		return (0);
	line->cmd->cmd = malloc(1);
	*(line->cmd->cmd) = 0;
	while (line->line[count] == '|' || !line->cmd_nbr)
	{
		if ((count = ft_pipe_check(line, count)) < 0)
			return (0);
		count = ft_cmd_recup(&(line->line), count, line->cmd);
		ft_printf("s2: %s: command not found\n", line->cmd->cmd);
		system(line->line);
		if (line->line[count] == ' ' || line->line[count] == '\t')
			count = ft_msg_recup(&line->line, count, line->cmd);
		line->cmd_nbr++;
	}
	return (1);
}
