/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 10:24:34 by igor              #+#    #+#             */
/*   Updated: 2021/02/04 14:26:20 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_hasvalue(char *envp)
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

int		ft_env(t_cmd *cmd, char **envp)
{
	int i;

	if (cmd->arg_nbr > 0)
	{
		ft_printf("too many arguments\n");
		return (-1);
	}
	i = 0;
	while (envp[i])
	{
		if (ft_hasvalue(envp[i]))
			ft_printf("%s\n", envp[i]);
		i++;
	}
	return (1);
}

char	*ft_getenv(char *name, char **envp)
{
	int	index;
	int len;

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

int		ft_putenv(char *string, char ***envp)
{
	int		index;
	int		len;
	char	**new_envp;

	index = 0;
	len = 0;
	while (string[len] != '=' && string[len])
		len++;
	while ((*envp)[index])
	{
		if (!ft_strncmp((*envp)[index], string, len + 1))
		{
			if (!is_in_stack((*envp)[index]))
				free((*envp)[index]);
			if (!((*envp)[index] = ft_strdup(string)))
				return (0);
			return (1);
		}
		index++;
	}
	if (!(new_envp = malloc(sizeof(char *) * (index + 2))))
		return (0);
	if (!(new_envp[index] = ft_strdup(string)))
	{
		free(new_envp);
		return (0);
	}
	new_envp[index + 1] = 0;
	while (index--)
		new_envp[index] = (*envp)[index];
	if (!is_in_stack(*envp))
		free(*envp);
	*envp = new_envp;
	return (1);
}
