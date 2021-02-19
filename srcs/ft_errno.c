#include "../includes/minishell.h"

int	ft_errno(t_cmd *cmd)
{
	int	ret;

	if (errno == EISDIR)
	{
		ft_printf("minishell: %s: is a directory\n", cmd->name);
		ret = 126;
	}
	else if (errno == EACCES)
	{
		ft_printf("minishell: %s: Permission denied\n", cmd->name);
		ret = 126;
	}
	else if (errno == ENOENT)
	{
		if (cmd->name[0] == '/' || (cmd->name[0] == '.' && cmd->name[1] == '/'))
			ft_printf("minishell: %s: No such file or directory\n", cmd->name);
		else
			ft_printf("minishell: %s: command not found\n", cmd->name);
		ret = 127;
	}
	else
		return (0);
	return (ret);
}