/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gorban <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:40:36 by gorban            #+#    #+#             */
/*   Updated: 2019/11/21 17:04:32 by gorban           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft.h"

int		check_comb(va_list ap, char *array, long flags[6]);
int		parse(va_list ap, long flags[6]);
int		ft_printf(const char *array, ...);
void	ft_write_nbr(int fd, long nbr, long flags[6]);
void	ft_write(int fd, char *c, int size, long flags[6]);
int		ft_isspecifier(char c);
int		ft_isflag(char c);
int		parse_int(long leint, long flags[6]);
int		parse_char(char lechar, long flags[6]);
int		parse_string(char *lastring, long flags[6]);
int		parse_hex(char *lhexa, long flags[6]);
int		parse_address(char *address, long flags[6]);

#endif
