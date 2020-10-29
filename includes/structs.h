/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:05:29 by ijacquet          #+#    #+#             */
/*   Updated: 2020/10/29 16:51:11 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_commande
{
	char	*cmd;
	int		cmd_id;
	int		optn_id;
	char	*msg;
}				t_cmd;

typedef struct s_line
{
	char	*line;
	int		cmd_nbr;
	t_cmd	*cmd;
}				t_line;

typedef struct	s_data
{
	int		line_nbr;
	t_line	*line;
}				t_data;

#endif