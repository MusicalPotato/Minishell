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
