/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:57:11 by ijacquet          #+#    #+#             */
/*   Updated: 2021/03/02 14:09:27 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define SINERR "minishell: syntax error near unexpected token "


# include <stdio.h>

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "structs.h"
# include "signal.h"


unsigned short	g_inexec;

int				ft_line_reader(t_data **data);
int				ft_parse_info(t_data *line);
int				ft_msg_recup(char *line, int count, t_cmd *cmd);
int				ft_parse_env(t_data *data, char ***envp, int *status);

int				ft_line_saver(t_data **data, char **line);
int				ft_check_text(int count, char **line);
int				ft_ask_next(char **line);

t_data			*ft_lstnew_line(char *content);
int				ft_lstadd_back_line(t_data **alst, t_data *new);
void			ft_lstclear_line(t_data **lst);

t_cmd			*ft_lstnew_cmd(char *content);
int				ft_lstadd_back_cmd(t_cmd **alst, t_cmd *new);
void			ft_lstclear_cmd(t_cmd **lst);

int				ft_is_space(char line);
int				ft_istext(int text, char c);
char			*ft_strndup(const char *s1, int size);
int				exit_write(char *msg, char *bonus, int value);
int				free_all(char ***data, int ret);
int				ft_hasslash(char *string);

int				ft_setup_exec(t_cmd *cmd, char ***envp, int *status);
void			ft_sorter(t_cmd *cmd, t_rdir pipe_rd, char ***envp, int *ret);
int				ft_exec(t_cmd *cmd, t_rdir pipe_rd, char **envp);

int             check_if_pipe(t_cmd *cmd);
int	        	remove_after_pipe(t_cmd *cmd, int index_pipe);
int     		remove_befor_pipe(t_cmd *cmd, int index_pipe);

int				ft_cd(t_cmd *cmd, t_rdir pipe_rd, char ***envp);
int				ft_echo(t_cmd *cmd);
int				ft_env(t_cmd *cmd, char **envp);
int				ft_export(t_cmd *cmd, char ***envp);
int				ft_pwd(t_cmd *cmd);
int				ft_unset(t_cmd *cmd, char ***envp);
int				ft_exit(t_cmd *cmd, int i);

int				ft_file_create(t_cmd *cmd);
int				ft_file_recup(t_cmd *cmd);
int				remove_after_red(t_cmd *cmd, int index_red);
void			ft_file_rd(t_cmd *cmd, t_rdir *rdir);
void			ft_pipe_rd(t_rdir *rdir, int filedes[2], int fd_def);
t_rdir			ft_open_all(t_rdir rdir);
void			ft_close_all(t_rdir rdir);

int				ft_display_export(char ***envp);
char			*ft_envformat(char *name, char *value);
int				ft_putshlvl(char *arg, char ***envp, int add);
void			ft_envpclear(char ***envp);
int				is_in_stack(void *addr);

int				ft_delenv(char *name, char ***envp);
char			*ft_getenv(char *name, char **envp);
int				ft_putenv(char *string, char ***envp, int to_free);
int				ft_setenv(char *name, char *value, int replace, char ***envp);
char			*ft_get_envname(char *envp);

void			handler(int signum);
int				ft_errno_exec(t_cmd *cmd, t_rdir pipe_rd, char *path, int emsg);
int				ft_errno2(t_cmd *cmd);

#endif
