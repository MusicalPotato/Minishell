/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleynts <tkleynts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:02:40 by gorban            #+#    #+#             */
/*   Updated: 2021/03/04 15:06:06 by tkleynts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int fd = open("jean.txt", O_WRONLY | O_CREAT);
	ft_printf("Hello world!");
	ft_fprintf(fd,"Hello world!");

	close(fd);


	return (19);
}
