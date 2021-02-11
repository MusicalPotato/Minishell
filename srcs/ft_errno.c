#include "../includes/minishell.h"

int	ft_errno(t_cmd *cmd)
{
	ft_printf("%s: ", cmd->name);
	if (errno == EACCES)
		return (exit_write("Permission denied: ", cmd->arg[0], -1));
	else if (errno == ENOENT)
		return (exit_write("No such file or directory: ", cmd->arg[0], -1));
	else
		return (exit_write("Error\n", 0, -1));
}