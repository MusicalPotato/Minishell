/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:02:19 by ijacquet          #+#    #+#             */
/*   Updated: 2020/11/06 14:55:31 by nlaurids         ###   ########.fr       */
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

	while (cmd->next)
		cmd = cmd->next;
	cmd->arg_nbr = -1;
	quote = 0;
	cmd->arg = malloc(0);
	while ((*line)[count] != '\n' && (*line)[count] != '\0' && (*line)[count] != '|')
	{
		while (ft_is_space((*line)[count]))
			count++;
		if ((*line)[count] == '\n' || (*line)[count] == '\0' || (*line)[count] == '|')
			break ;
		if ((*line)[count] != '\n')
		{
			cmd->arg_nbr++;
			cmd->arg = ft_stradd_back(cmd->arg, ft_strdup(0), cmd->arg_nbr);
		}
		while (quote || ((*line)[count] != '\n' && (*line)[count] != ' ' && (*line)[count] != '|' && (*line)[count] != '\0' && (*line)[count] != '\t'))
		{
			if ((*line)[count] == '\\' && (quote == 0 || (quote == 2 && ((*line)[count + 1] == '"' || (*line)[count + 1] == '\\'))))
			{
				count++;
				if ((*line)[count] != '\n')
					cmd->arg[cmd->arg_nbr] = ft_memcat(cmd->arg[cmd->arg_nbr], (*line) + count, ft_strlen(cmd->arg[cmd->arg_nbr]), 1);
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
				cmd->arg[cmd->arg_nbr] = ft_memcat(cmd->arg[cmd->arg_nbr], (*line) + count, ft_strlen(cmd->arg[cmd->arg_nbr]), 1);
				count++;
			}
		}
	}
	return (count);
}

int		ft_cmd_recup(char **line, int count, char **cmd)
{
	int quote;

	quote = 0;
	while ((*line)[count] != '\0' && (quote || ((*line)[count] != '\n' && (*line)[count] != ' ' && (*line)[count] != '|' && (*line)[count] != '\t')))
	{
		if ((*line)[count] == '\\' && (quote == 0 || (quote == 2 && ((*line)[count + 1] == '"' || (*line)[count + 1] == '\\'))))
		{
			count++;
			if ((*line)[count] != '\n')
				*cmd = ft_memcat(*cmd, (*line) + count, ft_strlen(*cmd), 1);
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
			*cmd = ft_memcat(*cmd, (*line) + count, ft_strlen(*cmd), 1);
			count++;
		}
	}
	return (count);
}

int		ft_pipe_check(t_line *line, int count, int x)
{
	if (x)
	{
		if (line->line[count] == '|')
		{
			count++;
			while (ft_is_space(line->line[count]))
				count++;
		}
		if (line->line[count] == '|')
		{
			ft_printf("parse error near `|'\n");
			return (-1);
		}
	}
	else if (line->line[count] == '|')
	{
		ft_printf("parse error near `|'\n");
		return (-1);
	}
	return (count);
}

int		ft_parser(t_data *data)
{
	int		count;
	char	*cmd;
	int		x;

	count = 0;
	x = 0;
	while (line->line[count] == '|' || !x)
	{
		cmd = malloc(1);
		*cmd = 0;
		if ((count = ft_pipe_check(line, count, x)) < 0)
			return (0);
		count = ft_cmd_recup(&(line->line), count, &cmd);
		if (!(ft_lstadd_back_cmd(&(line->cmd),
			ft_lstnew_cmd(ft_strdup(cmd)))))
			return (0);
		if (line->line[count] == ' ' || line->line[count] == '\t')
			count = ft_msg_recup(&line->line, count, line->cmd);
		free(cmd);
		x++;
	}
	return (1);
}
