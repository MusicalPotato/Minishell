#include "../includes/minishell.h"

int ft_echo(t_cmd *cmd)
{
    int     nl;
    int     i;

    i = 0;
    nl = 1;
    if (cmd->arg_nbr && !(ft_strncmp(cmd->arg[i], "-n", 3)))
    {
		nl = 0;
		i++;
    }
    while (i < cmd->arg_nbr)
    {
    	ft_printf("%s", cmd->arg[i]);
    	i++;
    	if (i < cmd->arg_nbr)
    		ft_printf(" ");
    }
    if (nl)
    	ft_printf("\n");
    return (1);
}