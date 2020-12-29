/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:57:11 by ijacquet          #+#    #+#             */
/*   Updated: 2020/12/08 08:53:06 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "structs.h"
# include "signal.h"

int		ft_line_reader(t_data **data);
int		ft_parse_info(t_data *line);
int		ft_parse_env(t_data *data, char ***envp);
int		ft_cmd_cmp(t_cmd *cmd, char ***envp);

t_data	*ft_lstnew_line(char *content);
int		ft_lstadd_back_line(t_data **alst, t_data *new);
void	ft_lstclear_line(t_data **lst);

t_cmd	*ft_lstnew_cmd(char *content);
int		ft_lstadd_back_cmd(t_cmd **alst, t_cmd *new);
void	ft_lstclear_cmd(t_cmd **lst);

int		ft_is_space(char line);
int		ft_istext(int text, char c);
char	*ft_strndup(const char *s1, int size);
int		exit_write(char *msg, char *bonus, int value);
int		free_all(char ***data, int ret);

int     ft_pwd(t_cmd *cmd);
int		ft_cd(t_cmd *cmd, char **envp);
int		ft_exec(t_cmd *cmd, char **envp);
int     ft_file_create(t_cmd *cmd);
int     ft_file_redirect(t_cmd *cmd);
int	    ft_open_close(int i, int fd, int std);
int 	ft_env(t_cmd *cmd, char **envp);
int     ft_unset(t_cmd *cmd, char ***envp);
int     ft_export(t_cmd *cmd, char ***envp);

char	*ft_envformat(char *name, char *value);
int		is_in_stack(void *addr);
void	ft_envpclear(char ***envp);

char	*ft_getenv(char *name, char **envp);
int		ft_setenv(char *name, char *value, int replace, char ***envp);
int		ft_putenv(char *string, char ***envp);
int     ft_delenv(char *name, char ***envp);


int     ft_exit(t_cmd *cmd);

#endif
