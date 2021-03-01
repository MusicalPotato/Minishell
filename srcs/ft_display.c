/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:33:33 by tkleynts          #+#    #+#             */
/*   Updated: 2021/03/01 15:36:45 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
