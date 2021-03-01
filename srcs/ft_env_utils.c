/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:03:55 by igor              #+#    #+#             */
/*   Updated: 2021/03/01 14:27:19 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_in_stack(void *addr)
{
	int		a;
	void	*stack;

	stack = &a;
	return (stack < addr);
}

char	*ft_envformat(char *name, char *value)
{
	char	*string;
	int		len;
	int		i;

	len = ft_strlen(name);
	if (!(string = malloc(sizeof(char) * (len + ft_strlen(value) + 2))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		string[i] = name[i];
		i++;
	}
	string[i++] = '=';
	while (value && value[i - len - 1])
	{
		string[i] = value[i - len - 1];
		i++;
	}
	string[i] = 0;
	return (string);
}

void	ft_envpclear(char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		if (!is_in_stack((*envp)[i]))
		{
			free((*envp)[i]);
			(*envp)[i] = NULL;
		}
		i++;
	}
	if (!is_in_stack((*envp)))
	{
		free((*envp));
		(*envp) = NULL;
	}
	return ;
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
		ft_printf(
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
