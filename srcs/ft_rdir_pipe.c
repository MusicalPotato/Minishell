#include "../includes/minishell.h"

int	check_if_pipe(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->arg_nbr)
	{
		if (!strncmp(cmd->arg[i], "|", 2))
			return (i);
		i++;
	}
	return (-1);
}

int	remove_after_pipe(t_cmd *cmd, int index_pipe)
{
	char	**lst;
	int		i;

	i = 0;
	lst = malloc(sizeof(char *) * (index_pipe));
	while (i < index_pipe)
	{
		lst[i] = cmd->arg[i];
		i++;
	}
	cmd->arg = lst;
	cmd->arg_nbr = index_pipe;
	return (1);
}

int	remove_befor_pipe(t_cmd *cmd, int index_pipe)
{
	char	**lst;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (index_pipe + size < cmd->arg_nbr)
		size++;
	lst = malloc(sizeof(char *) * (size - 1));
	cmd->name = cmd->arg[index_pipe + i + 1];
	while (i < size - 2)
	{
		lst[i] = cmd->arg[index_pipe + i + 2];
		i++;
	}
	cmd->arg = lst;
	cmd->arg_nbr = size - 2;
	return (1);
}

t_rdir	ft_redir_fd(t_rdir rdir, int filedes[2], int fd_def)
{
	if (fd_def == 1)
	{
		rdir.fdin = filedes[1];
		rdir.sdin = dup(1);
		dup2(rdir.fdin, 1);
	}
	else if (fd_def == 0)
	{
		rdir.fdout = filedes[0];
		rdir.sdout = dup(0);
		dup2(rdir.fdout, 0);
	}
	return (rdir);
}

int	ft_rdir_pipe(t_cmd *cmd, t_rdir *rdir, char ***envp)
{
	int		index_pipe;
	int		filedes[2];
	pid_t	childpid;

	while ((index_pipe = check_if_pipe(cmd)) > -1)
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
			remove_after_pipe(cmd, index_pipe);
            *rdir = ft_redir_fd(*rdir, filedes, 1);
			ft_cmd_cmp(cmd, envp);
            exit(0);
        }
        else
        {
            close(filedes[1]);
			remove_befor_pipe(cmd, index_pipe);
			*rdir = ft_redir_fd(*rdir, filedes, 0);
        }
	}
	return (1);
}
