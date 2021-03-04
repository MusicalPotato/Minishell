/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 04:18:23 by igor              #+#    #+#             */
/*   Updated: 2021/03/04 16:01:31 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		ft_fprintf(2,
	"minishell: warning: shell level (%d) too high, resetting to 1\n", nbr);
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

int		ft_ck_env(t_cmd *cmd, char ***envp, int i, char **envname)
{
	if (cmd->arg_nbr && ft_check_format_export(cmd->arg[i - 1]))
	{
		if (!(*envname = ft_get_envname(cmd->arg[i - 1])))
			return (-1);
		ft_putenv(ft_envformat("_", *envname), envp, 1);
		free(*envname);
	}
	return (0);
}

int		ft_export(t_cmd *cmd, char ***envp)
{
	int		i;
	int		ret;
	char	*envname;

	i = 0;
	ret = 0;
	while (i < cmd->arg_nbr)
	{
		if (!ft_check_format_export(cmd->arg[i]))
		{
			ft_fprintf(2,
			"minishell: export: `%s': not a valid identifier\n", cmd->arg[i]);
			ret = 1;
		}
		else if (!(ft_putenv(cmd->arg[i], envp, 0)))
			return (-1);
		i++;
	}
	if (ft_ck_env(cmd, envp, i, &envname) < 0)
		return (-1);
	if (!cmd->arg_nbr)
		ft_display_export(envp);
	return (ret);
}
