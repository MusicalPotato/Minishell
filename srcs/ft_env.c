/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 10:24:34 by igor              #+#    #+#             */
/*   Updated: 2021/03/04 16:00:52 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_hasvalue(char *envp)
{
	int	c;

	c = 0;
	while (envp[c])
	{
		if (envp[c] == '=')
			return (1);
		c++;
	}
	return (0);
}

int			ft_env(t_cmd *cmd, char **envp)
{
	int	i;

	if (cmd->argc > 0)
	{
		ft_fprintf(2, "too many arguments\n");
		return (255);
	}
	i = 0;
	while (envp[i])
	{
		if (ft_hasvalue(envp[i]))
			ft_printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

char		*ft_getenv(char *name, char **envp)
{
	int	index;
	int	len;

	index = 0;
	len = ft_strlen(name);
	while (envp[index])
	{
		if (!ft_strncmp(envp[index], name, len) && envp[index][len] == '=')
			return ((envp[index]) + len + 1);
		index++;
	}
	return (0);
}

static int	ft_replace_env(char ***envp, char *new_string, int len)
{
	int	index;

	index = 0;
	while ((*envp)[index])
	{
		if (!ft_strncmp((*envp)[index], new_string, len + 1))
		{
			if (!is_in_stack((*envp)[index]))
				free((*envp)[index]);
			(*envp)[index] = new_string;
			return (-1);
		}
		index++;
	}
	return (index);
}

int			ft_putenv(char *string, char ***envp, int to_free)
{
	int		index;
	int		len;
	char	**new_envp;
	char	*new_string;

	len = 0;
	new_string = ft_strdup(string);
	if (to_free)
		free(string);
	if (!new_string)
		return (0);
	while (new_string[len] != '=' && new_string[len])
		len++;
	if ((index = ft_replace_env(envp, new_string, len)) < 0)
		return (1);
	if (!(new_envp = malloc(sizeof(char *) * (index + 2))))
		return (0);
	new_envp[index] = new_string;
	new_envp[index + 1] = 0;
	while (index--)
		new_envp[index] = (*envp)[index];
	if (!is_in_stack(*envp))
		free(*envp);
	*envp = new_envp;
	return (1);
}
