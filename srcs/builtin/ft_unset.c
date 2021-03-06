/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:14:32 by tkleynts          #+#    #+#             */
/*   Updated: 2021/03/04 16:02:53 by tkleynts         ###   ########.fr       */
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

	i = 1;
	ret = 0;
	while (i <= cmd->argc)
	{
		if (!ft_check_format_unset(cmd->argv[i]))
		{
			ft_fprintf(2, "minishell: unset: `%s': not a valid identifier\n",
					cmd->argv[i]);
			ret = 1;
		}
		else
			ft_unsetenv(cmd->argv[i], envp);
		i++;
	}
	return (ret);
}
