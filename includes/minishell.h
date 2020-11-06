/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:57:11 by ijacquet          #+#    #+#             */
/*   Updated: 2020/11/05 15:43:41 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>

# include <stdlib.h>
# include "../libft/libft.h"
# include "structs.h"

int		ft_line_reader(t_data **data);
int		ft_parser(t_data *line);

t_data	*ft_lstnew_line(char *content);
int		ft_lstadd_back_line(t_data **alst, t_data *new);
void	ft_lstclear_line(t_data **lst);

t_cmd	*ft_lstnew_cmd(char *content);
int		ft_lstadd_back_cmd(t_cmd **alst, t_cmd *new);
void	ft_lstclear_cmd(t_cmd **lst);

int		ft_is_space(char line);
int		ft_istext(int text, char c);
char	*ft_strndup(const char *s1, int size);

#endif
