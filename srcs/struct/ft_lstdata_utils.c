/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdata_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igor <igor@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:36:42 by ijacquet          #+#    #+#             */
/*   Updated: 2021/03/16 00:16:37 by igor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	*ft_lstnew_data(char **envp)
{
	t_data	*list;

	if (!(list = malloc(sizeof(t_data))))
		return (0);
	list->status = 0;
	list->envp = envp;
	list->cmd = NULL;
	list->fd = 0;
	list->index = 0;
	list->hist = NULL;
	if (tcgetattr(0, &(list->termios)) == -1
	|| tcgetattr(0, &(list->termios_backup)) == -1)
	{
		free(list);
		return (0);
	}
	list->termios.c_lflag &= ~(ICANON);
	list->termios.c_lflag &= ~(ECHO);
	return (list);
}

void	ft_lstclear_data(t_data **lst)
{
	(*lst)->status = 0;
	ft_envpclear(&((*lst)->envp));
	(*lst)->envp = NULL;
	ft_lstclear_cmd(&((*lst)->cmd));
	close((*lst)->fd);
	(*lst)->fd = 0;
	(*lst)->index = 0;
	ft_lstclear_hist(&(*lst)->hist);
	tcsetattr(0, 0, &((*lst)->termios_backup));
	free(*lst);
	*lst = NULL;
}
