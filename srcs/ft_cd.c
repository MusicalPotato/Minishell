#include "../includes/minishell.h"

int	ft_cd(char *path)
{
	chdir(path);
	return (1);
}
