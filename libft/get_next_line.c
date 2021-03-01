/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:13:16 by gorban            #+#    #+#             */
/*   Updated: 2021/03/01 13:13:46 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		complet_line(char **line, char (*rest)[BUFFER_SIZE + 1])
{
	int	a;
	int	b_size;

	a = 0;
	b_size = 0;
	while ((*rest)[b_size] && (*rest)[b_size] != '\n')
		b_size++;
	if (!(*line = ft_memcat(*line, *rest, ft_strlen(*line), b_size)))
		return (0);
	b_size -= -1;
	while ((*rest)[b_size])
	{
		(*rest)[a] = (*rest)[b_size];
		a -= -1;
		b_size -= -1;
	}
	while ((*rest)[a])
	{
		(*rest)[a] = '\0';
		a -= -1;
	}
	return (1);
}

int		check_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] == '\n')
			return (1);
	return (0);
}

int		reading(char (*line)[BUFFER_SIZE + 1], int fd)
{
	int		read_size;
	int		i;
	char	*buf;

	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	i = 0;
	buf[BUFFER_SIZE] = '\0';
	read_size = read(fd, buf, BUFFER_SIZE);
	if (read_size <= 0)
	{
		free(buf);
		return (read_size);
	}
	while (i < read_size)
	{
		(*line)[i] = buf[i];
		i++;
	}
	(*line)[i] = '\0';
	free(buf);
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	rest[FOPEN_MAX + 1][BUFFER_SIZE + 1];
	int			r;

	if (!line || fd > FOPEN_MAX || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!(*line = malloc(sizeof(char))))
		return (-1);
	**line = '\0';
	while (!check_line(rest[fd]))
	{
		if (!(complet_line(line, &(rest[fd]))))
			return (ft_freeturn(line, -1));
		if ((r = reading(&(rest[fd]), fd)) < 0)
			return (ft_freeturn(line, -1));
		else if (r == 0)
			return (0);
	}
	if (!(complet_line(line, &rest[fd])))
		return (ft_freeturn(line, -1));
	return (1);
}
