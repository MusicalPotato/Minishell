#include "../libft/libft.h"

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
	while (value[i - len - 1])
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
