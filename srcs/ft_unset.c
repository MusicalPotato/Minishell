#include "../includes/minishell.h"

int		ft_unsetenv(char *name, char ***envp)
{
    int     i;
    int		index;
	int 	len;
    char    *temp;

	index = 0;
    len = ft_strlen(name);
	while ((*envp)[index])
	{
        if (!ft_strncmp((*envp)[index], name, len) && (*envp)[index][len] == '=')
		{
            temp = (*envp)[index];
            i = index;
        	while ((*envp)[i])
            {
        		(*envp)[i] = (*envp)[i + 1];
                i++;
            }
            printf("free : %s\n", temp);
            free(temp);
        }
        else
		    index++;
	}
	return (1);
}

int     ft_unset(t_cmd *cmd, char ***envp)
{
    int x;
    int i;

    i = 0;
    while (i < cmd->arg_nbr)
    {
        x = 0;
        while (ft_isalnum(cmd->arg[i][x]) || cmd->arg[i][x] == '_')
			x++;
        if (cmd->arg[i][x])
            ft_printf("unset: %s: invalid parameter name\n", cmd->arg[i]);
        else if (!(ft_unsetenv(cmd->arg[i], envp)))
            return (0);
        i++;
    }
    return (1);
}
