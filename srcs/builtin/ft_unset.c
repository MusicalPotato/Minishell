/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:14:32 by tkleynts          #+#    #+#             */
/*   Updated: 2021/03/01 13:38:27 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_check_format_unset(char *arg)
{
	int i;

	i = 0;
	if (ft_isdigit(arg[i]))
		return (0);
	while (ft_isalnum(arg[i]) || arg[i] == '_')
		i++;
	if (arg[i])
		return (0);
	if (i == 0)
		return (0);
	return (1);
}

void	ft_unsetenv(char *name, char ***envp)
{
	int		i;
	int		index;
	int		len;
	char	*temp;

	index = 0;
	len = ft_strlen(name);
	while ((*envp)[index])
	{
		if (!ft_strncmp((*envp)[index], name, len) &&
				(*envp)[index][len] == '=')
		{
			temp = (*envp)[index];
			i = index;
			while ((*envp)[i])
			{
				(*envp)[i] = (*envp)[i + 1];
				i++;
			}
			if (!is_in_stack(temp))
				free(temp);
		}
		else
			index++;
	}
}

int		ft_unset(t_cmd *cmd, char ***envp)
{
	int i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < cmd->arg_nbr)
	{
		if (!ft_check_format_unset(cmd->arg[i]))
		{
			ft_printf("minishell: unset: `%s': not a valid identifier\n",
					cmd->arg[i]);
			ret = 1;
		}
		else
			ft_unsetenv(cmd->arg[i], envp);
		i++;
	}
	return (ret);
}
