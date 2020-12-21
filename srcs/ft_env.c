/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 10:24:34 by igor              #+#    #+#             */
/*   Updated: 2020/12/08 10:24:37 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

int is_in_stack(void *addr)
{
	int		a;
    void	*stack;

	stack = &a;
	printf("%p < %p ?\n", stack, addr);
    return (stack < addr);
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
		printf ("adress %p is in stack ? %d\n", envp[i], is_in_stack(envp[i]));
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
	while (envp[index])
	{
		len = ft_lentoequal(name);
		if (len < ft_lentoequal(envp[index]))
			len = ft_lentoequal(envp[index]);
		if (!ft_strncmp(envp[index], name, len))
			return ((envp[index]) + len + 1);
		index++;
	}
	return (0);
}

int		ft_putenv(char *string, char ***envp)
{
	int		index;
	int 	len;
	char	**new_envp;
	
	index = 0;
	while ((*envp)[index])
	{
		len = ft_lentoequal(string);
		if (len < ft_lentoequal((*envp)[index]))
			len = ft_lentoequal((*envp)[index]);
		if (!ft_strncmp((*envp)[index], string, len))
		{
			if (!((*envp)[index] = ft_strdup(string)))
				return (0);
			return (1);
		}
		index++;
	}
	if (!(new_envp = malloc(sizeof(char *) * (index + 2))))
		return (0);
	if (!(new_envp[index] = ft_strdup(string)))
		return (0);
	new_envp[index + 1] = 0;
	while (index--)
		new_envp[index] = (*envp)[index];
	*envp = new_envp;
	return (1);
}

int		ft_setenv(char *name, char *value, int replace, char ***envp)
{
	char	*old_val;
	char	*string;
	
	old_val = ft_getenv(name, *envp);
	if (!replace && old_val)
		return (1);
	if (!(string = ft_envformat(name, value)))
		return (0);
	if (!(ft_putenv(string, envp)))
		return (ft_freeturn(&string, 0));
	return (1);
}
