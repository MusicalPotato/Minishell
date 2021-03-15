/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:05:29 by ijacquet          #+#    #+#             */
/*   Updated: 2021/03/16 00:31:27 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_rdir
{
	int					fdin;
	int					fdout;
	int					sdin;
	int					sdout;
}				t_rdir;

typedef struct	s_envdata
{
	char				*var;
	int					s_var;
	char				*val;
	int					s_val;
	int					count;
}				t_ed;

typedef struct	s_history
{
	char				*line;
	struct s_history	*next;
	struct s_history	*prev;
}				t_hist;

typedef struct	s_commande
{
	char				*line;
	char				**argv;
	int					argc;
	struct s_commande	*next;
}				t_cmd;

typedef struct	s_data
{
	int					status;
	int					inexec;
	char				**envp;
	t_cmd				*cmd;
	int					fd;
	int					index;
	t_hist				*hist;
	struct termios		termios;
	struct termios		termios_backup;
}				t_data;

#endif
