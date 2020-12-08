/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:05:29 by ijacquet          #+#    #+#             */
/*   Updated: 2020/12/07 18:37:20 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_commande
{
	char				*name;
	char				**arg;
	int					arg_nbr;
	struct s_commande	*next;
}				t_cmd;

typedef struct s_data
{
	char			*line;
	t_cmd			*cmd;
	struct s_data	*next;
}				t_data;

#endif
