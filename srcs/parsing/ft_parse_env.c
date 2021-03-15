/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 03:41:32 by igor              #+#    #+#             */
/*   Updated: 2021/03/06 14:24:20 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_write_newstr(char **newstr, char **str, t_ed *ted, int n)
{
	int	a;

	a = 0;
	while (a < ted->count - 1)
	{
		(*newstr)[a] = (*str)[a];
		a++;
	}
	while (a < ted->count + ted->s_val - 1)
	{
		if (ted->val[a - ted->count + 1] == '\\')
		{
			(*newstr)[a + n] = '\\';
			n++;
		}
		(*newstr)[a + n] = ted->val[a - ted->count + 1];
		a++;
	}
	while ((*str)[a - ted->s_val + ted->s_var + 1])
	{
		(*newstr)[a + n] = (*str)[a - ted->s_val + ted->s_var + 1];
		a++;
	}
	(*newstr)[a + n] = 0;
}

int		var_to_value(t_ed *ted, char **str)
{
	char	*newstr;
	int		n;

	ted->s_val = ft_strlen(ted->val);
	n = ft_countbs(ted->val);
	if (!(newstr = malloc(sizeof(char) *
		(ft_strlen(*str) - ted->s_var + ted->s_val + n))))
		return (exit_write("malloc Error\n", 0, 0));
	ft_write_newstr(&newstr, str, ted, 0);
	if (*str)
		free(*str);
	*str = newstr;
	return (1);
}

int		ft_get_envinfo2(t_data *d, t_cmd *cmd, t_ed *ted)
{
	int to_free;

	to_free = 0;
	if (ted->var[0] == '?')
	{
		if (!(ted->val = ft_itoa(d->status)))
			return (exit_write("malloc Error\n", 0, 0));
		to_free = 1;
	}
	else
		ted->val = ft_getenv(ted->var, d->envp);
	if (!(var_to_value(ted, &cmd->line)))
	{
		if (to_free)
			free(ted->val);
		return (ft_freeturn(&ted->var, 0));
	}
	if (to_free)
		free(ted->val);
	ted->count--;
	return (1);
}

int		ft_get_envinfo(t_data *d, t_cmd *cmd, t_ed *ted)
{
	ted->count++;
	if (cmd->line[ted->count + ted->s_var] != '?')
		while (ft_isalnum(cmd->line[ted->count + ted->s_var])
				|| cmd->line[ted->count + ted->s_var] == '_')
			ted->s_var++;
	else
		ted->s_var++;
	if (!(ted->var = ft_memcat(ted->var, cmd->line + ted->count,
								0, ted->s_var)))
		return (exit_write("malloc Error\n", 0, 0));
	if (ted->var[0])
		if (!(ft_get_envinfo2(d, cmd, ted)))
			return (0);
	free(ted->var);
	ted->var = NULL;
	return (1);
}

int		ft_parse_env(t_data *d, t_cmd *cmd)
{
	t_ed	*ted;
	int		quote;

	if (!(ted = ft_lstnew_envdata()))
		return (-1);
	quote = 0;
	while (cmd->line[ted->count])
	{
		quote = ft_istext(quote, cmd->line[ted->count]);
		if (quote != 1 && cmd->line[ted->count] == '\\')
			ted->count += 2;
		if (quote != 1 && cmd->line[ted->count] == '$')
		{
			if (!(ft_get_envinfo(d, cmd, ted)))
				return (-1);
		}
		else
			ted->count++;
	}
	return (0);
}
