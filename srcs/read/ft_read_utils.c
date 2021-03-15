#include "../../includes/minishell.h"

int		ft_outc(int c)
{
	return ((int)write(STDIN_FILENO, &c, 1));
}
