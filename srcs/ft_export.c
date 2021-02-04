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

int	ft_check_format(char *arg)
{
	int i;

	i = 0;
	if (!ft_isalpha(arg[i]))
		return (0);
	i++;
	while (ft_isalnum(arg[i]) || arg[i] == '_')
		i++;
	if (arg[i] != '=')
		return (0);
	i++;
	while (arg[i])
	{
		if (!ft_isprint(arg[i]) || ft_is_space(arg[i]) ||
							arg[i] == '&' || arg[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_cmd *cmd, char ***envp)
{
	int i;

	i = 0;
	while (i < cmd->arg_nbr)
	{
		if (!ft_check_format(cmd->arg[i]))
			ft_printf("export: `%s': not a valid identifier\n", cmd->arg[i]);
		else if (!(ft_putenv(cmd->arg[i], envp)))
			return (0);
		i++;
	}
	return (1);
}
