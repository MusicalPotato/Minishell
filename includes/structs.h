/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:05:29 by ijacquet          #+#    #+#             */
/*   Updated: 2021/02/19 15:14:56 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_rdir
{
	int	fdin;
	int	fdout;
	int	sdin;
	int	sdout;
}				t_rdir;

typedef struct	s_history
{
	char				*line;
	struct s_history	*next;
	struct s_history	*prev;
}				t_hist;

typedef struct	s_commande
{
	char				*name;
	char				**arg;
	int					arg_nbr;
	struct s_commande	*next;
}				t_cmd;

typedef struct	s_data
{
	char			*line;
	t_cmd			*cmd;
	struct s_data	*next;
}				t_data;

#endif
