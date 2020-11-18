#include "../libft/libft.h"

int		ft_lentoequal(char *str)
{
	int size;

	size = 0;
	if (!str)
		return (0);
	while (str[size] && str[size] != '=')
		size++;
	return (size);
}

char	*ft_getenv(char *name, char **envp)
{
	int	index;
	int len;

	index = 0;
	while (envp[index])
	{
		if ((len = ft_lentoequal(name)) < ft_lentoequal(envp[index]))
			len = ft_lentoequal(envp[index]);
		if (!ft_strncmp(envp[index], name, len))
		{
			return ((envp[index]) + len + 1);
		}
		index++;
	}
	return (0);
}
/*
int		ft_setenv(char *name, char *value, int replace, char ***envp)
{

}

int		ft_putenv(char *string, char ***envp)
{

}*/
