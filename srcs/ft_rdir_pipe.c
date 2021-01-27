#include "../includes/minishell.h"

int	check_if_pipe(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!strncmp(arg[i], "|", 2))
			return (i);
		i++;
	}
	return (0);
}

int	remove_after_pipe(t_cmd *cmd, int index_pipe)
{
	char	**lst;
	int		i;

	i = 0;
	lst = malloc(sizeof(char *) * (index_pipe + 1));
	while (i < index_pipe)
	{
		lst[i] = cmd->arg[i];
		i++;
	}
	lst[i] = 0;
	cmd->arg = lst;
	return (1);
}

int	remove_befor_pipe(t_cmd *cmd, int index_pipe)
{
	char	**lst;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (cmd->arg[index_pipe + size])
		size++;
	lst = malloc(sizeof(char *) * (size));
	while (i < size)
	{
		lst[i] = cmd->arg[index_pipe + i + 1];
		i++;
	}
	cmd->arg = lst;
	return (1);
}

ft_redir_fd(t_rdir rdir, int fd_def, int new_fd)
{
	if (rdir.fdin > 0)
	{
		rdir.sdin = dup(1);
		dup2(rdir.fdin, 1);
	}
	if (rdir.fdout > 0)
	{
		rdir.sdout = dup(0);
		dup2(rdir.fdout, 0);
	}
	return (rdir);
}

int	ft_rdir_pipe(t_cmd *cmd, t_rdir rdir, char ***envp)
{
	int		index_pipe;
	int		filedes[2];
	int		nbytes;
	pid_t	childpid;

	while (index_pipe = check_is_pipe(cmd->arg))
	{
		pipe(filedes);
		if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }
        if(childpid == 0)
        {
            close(filedes[0]);
            //redirection fd 1 -> filedes[1](fd child)
			remove_after_pipe(cmd, index_pipe);
			ft_cmd_cmp(cmd, envp);
            exit(0);
        }
        else
        {
            close(filedes[1]);
			remove_befor_pipe(cmd, index_pipe);
			//redirection fd 0 -> filedes[0](fd parent)
        }
	}
	return (1);
}
