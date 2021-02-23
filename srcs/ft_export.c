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

int		ft_putshlvl(char *arg, char ***envp, int add)
{
	int		nbr;
	char	*value;

	if (!arg)
		nbr = 1;
	else
		nbr = ft_atoi(arg) + add;
	if (nbr > 2000000)
	{
		ft_printf("minishell: warning: shell level (%d) too high, resetting to 1\n", nbr);
		nbr = 1;
	}
	else if (nbr <= -1999999)
		nbr = 0;
	if (!(value = ft_itoa(nbr)))
		return (0);
	if (!(ft_putenv(ft_envformat("SHLVL", value), envp, 1)))
		return (ft_freeturn(&value, 0));
	return (ft_freeturn(&value, 1));
}

void	ft_display_value(char *value)
{
	int	i;

	i = 0;
	ft_printf("=\"");
	while (value[i])
	{
		if (value[i] == '\\'|| value[i] == '$'|| value[i] == '\"')
			ft_printf("\\");
		ft_printf("%c", value[i]);
		i++;
	}
	ft_printf("\"");
}

int		ft_display_export(char ***envp)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while ((*envp)[i])
		{
			if (!(name = ft_get_envname((*envp)[i])))
				return (-1);
			if (ft_strncmp(name, "_", 2))
			{
				ft_printf("declare -x %s", name);
				value = ft_getenv(name, *envp);
				if (value)
					ft_display_value(value);
				ft_printf("\n");
			}
			free(name);
			i++;
		}
	return (1);
}

int		ft_export(t_cmd *cmd, char ***envp)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < cmd->arg_nbr)
	{
		if (!ft_check_format_export(cmd->arg[i]))
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n", cmd->arg[i]);
			ret = 1;
		}
		else if (!(ft_putenv(cmd->arg[i], envp, 0)))
			return (-1);
		i++;
	}
	if (i == 0)
		ft_display_export(envp);
	return (ret);
}
