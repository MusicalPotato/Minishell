/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 04:18:23 by igor              #+#    #+#             */
/*   Updated: 2021/03/01 14:29:32 by nlaurids         ###   ########.fr       */
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

void	ft_display_value(char *value)
{
	int	i;

	i = 0;
	ft_printf("=\"");
	while (value[i])
	{
		if (value[i] == '\\' || value[i] == '$' || value[i] == '\"')
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

int		ft_export2(t_cmd *cmd, char ***envp, int i)
{
	char	*envname;

	if (cmd->arg_nbr && ft_check_format_export(cmd->arg[i - 1]))
	{
		if (!(envname = ft_get_envname(cmd->arg[i - 1])))
			return (-1);
		ft_putenv(ft_envformat("_", envname), envp, 1);
		free(envname);
	}
	if (!cmd->arg_nbr)
		ft_display_export(envp);
	return (0);
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
			ft_printf("minishell: export: `%s': not a valid identifier\n",
					cmd->arg[i]);
			ret = 1;
		}
		else if (!(ft_putenv(cmd->arg[i], envp, 0)))
			return (-1);
		i++;
	}
	if (ft_export2(cmd, envp, i - 1))
		return (-1);
	return (ret);
}
