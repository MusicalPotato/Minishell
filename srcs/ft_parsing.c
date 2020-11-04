/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:02:19 by ijacquet          #+#    #+#             */
/*   Updated: 2020/11/04 16:19:29 by igor             ###   ########.fr       */
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
int		ft_msg_recup(char **line, int count, char **msg)
{
	int quote;
	int	msg_nbr;

	msg_nbr = -1;
	quote = 0;
	while ((*line)[count] != '\n')
	{
		while (ft_is_space((*line)[count]))
			count++;
		if ((*line)[count] != '\n')
		{
			msg_nbr++;
			msg = malloc(sizeof(char *) * (msg_nbr + 1));
			msg[msg_nbr] = malloc(1);
			*msg[msg_nbr] = 0;
		}
		while (quote || ((*line)[count] != '\n' && (*line)[count] != ' ' && (*line)[count] != '|'))
		{
			if ((*line)[count] == '\\' && (quote == 0 || (quote == 2 && ((*line)[count + 1] == '"' || (*line)[count + 1] == '\\'))))
			{
				count++;
				if ((*line)[count] != '\n')
					msg[msg_nbr] = ft_memcat(msg[msg_nbr], (*line) + count, ft_strlen(msg[msg_nbr]), 1);
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
				msg[msg_nbr] = ft_memcat(msg[msg_nbr], (*line) + count, ft_strlen(msg[msg_nbr]), 1);
				count++;
			}
		}
	printf("Message n°%d : %s\n", msg_nbr + 1, msg[msg_nbr]);
	}
	return (1);
}

int		ft_cmd_recup(char **line, int count, t_cmd *cmd)
{
	int quote;

	quote = 0;
	while ((*line)[count] != '\0' && (quote || ((*line)[count] != '\n' && (*line)[count] != ' ' && (*line)[count] != '|')))
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
	if ((*line)[count] == ' ')
		ft_msg_recup(line, count, cmd->msg);
	return (1);
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
		ft_cmd_recup(&(line->line), count, line->cmd);
		line->cmd_nbr++;
	}
	ft_printf("s2: %s: command not found\n", line->cmd->cmd);
	system(line->line);
	return (1);
}
