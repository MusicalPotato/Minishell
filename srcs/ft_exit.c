#include "../includes/minishell.h"

int	ft_exit(t_cmd *cmd)
{
	int	i;

	i = 0;
	//ft_printf("exit\n");
	if (cmd->arg_nbr)
	{
		while (ft_is_space(cmd->arg[0][i]))
			i++;
		if (cmd->arg[0][i] == '+' || cmd->arg[0][i] == '-')
			i++;
		while (ft_isdigit(cmd->arg[0][i]))
			i++;
		while (cmd->arg[0][i])
		{
			if (cmd->arg[0][i] != ' ' && cmd->arg[0][i] != '\t')
			{
				ft_printf("minishell: exit: %s: numeric argument required\n", cmd->arg[0]);
				exit(255);
			}
			i++;
		}
		if (cmd->arg_nbr > 1)
		{
			ft_printf("minishell: exit: too many arguments\n");
			return (-1);
		}
		i = ft_atoi(cmd->arg[0]);
		if (i == -1 && ft_strncmp(cmd->arg[0], "-1", 3))
			ft_printf("minishell: exit: %s: numeric argument required\n", cmd->arg[0]);
		//printf("atoi = %d\n", i);
		exit(i);
	}
	exit(0);
	return (0);
}
