#include "../includes/minishell.h"

int	var_to_value(char **str, int count, int s_var, char *val)
{
	char *newstr;
	int s_val;
	int a;

	s_val = ft_strlen(val);
	newstr = malloc(sizeof(char) * (ft_strlen(*str) - s_var + s_val));
	a = 0;
	while (a < count - 1)
	{
		newstr[a] = (*str)[a];
		a++;
	}
	while (a < count + s_val - 1)
	{
		newstr[a] = val[a - count + 1];
		a++;
	}
	while ((*str)[a - s_val + s_var + 1])
	{
		newstr[a] = (*str)[a - s_val + s_var + 1];
		a++;
	}
	newstr[a] = '\0';
	free(*str);
	*str = newstr;
	return (1);
}

int	ft_parse_env(t_data *d, char **envp)
{
	char	*var;
	char	*value;
	int		count;
	int 	s_v;
	int		quote;

	count = 0;
	quote = 0;
	while (d->line[count])
	{
		s_v = 0;
		var = NULL;
		quote = ft_istext(quote, d->line[count]);
		if (!quote && d->line[count] == '$')
		{
			count++;
			while (ft_isalnum(d->line[count + s_v]) || d->line[count + s_v] == '_')
			{
				var = ft_memcat(var, d->line + count + s_v, ft_strlen(var), 1);
				s_v++;
			}
			if (var)
			{
				ft_printf("var = %s\n", var);
				value = ft_getenv(var, envp);
				ft_printf("value = %s\n", value);
				var_to_value(&d->line, count, s_v, value);
			}
			free(var);
		}
		else
			count++;
	}
	ft_printf("newstr is : %s\n", d->line);
	return (1);
}