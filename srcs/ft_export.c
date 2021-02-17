/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 04:18:23 by igor              #+#    #+#             */
/*   Updated: 2021/02/04 13:54:27 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_check_format_export(char *arg)
{
	int i;

	i = 0;
	if (ft_isdigit(arg[i]))
		return (0);
	while (ft_isalnum(arg[i]) || arg[i] == '_')
		i++;
	if (arg[i] != '=' && arg[i])
		return (0);
	if (i == 0)
		return (0);
	return (1);
}

char	*ft_get_envname(char *envp)
{
	char	*name;
	int		len;

	name = NULL;
	len = 0;
	while (envp[len] && envp[len] != '=')
		len++;
	if (!(name = ft_memcat(name, envp, 0, len)))
		return (NULL);
	return (name);
}

int		ft_export(t_cmd *cmd, char ***envp)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (i < cmd->arg_nbr)
	{
		if (!ft_check_format_export(cmd->arg[i]))
			ft_printf("minishell: export: `%s': not a valid identifier\n", cmd->arg[i]);
		else if (!(ft_putenv(cmd->arg[i], envp, 0)))
			return (0);
		i++;
	}
	if (i == 0)
	{
		while ((*envp)[i])
		{
			if (!(name = ft_get_envname((*envp)[i])))
				return (0);
			value = ft_getenv(name, *envp);
			if (ft_strncmp(name, "_", 2))
			{
				ft_printf("declare -x %s", name);
				if (value)
					ft_printf("=\"%s\"", value);
				ft_printf("\n");
			}
			free(name);
			i++;
		}
	}
	return (1);
}
