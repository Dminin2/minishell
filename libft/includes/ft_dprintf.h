/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 23:45:16 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/07 23:45:18 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_dprintf(int fd, const char *format, ...);
int	dprint_char(int fd, int n);
int	dprint_string(int fd, char *str);
int	dprint_percent(int fd);
int	dprint_pointer(int fd, void *ptr);
int	dprint_decimal(int fd, int nbr);
int	dprint_unsigned_decimal(int fd, unsigned int nbr);
int	dprint_hexadecimal(int fd, unsigned int nbr, int hex_case);

int	ft_dputchar_fd_error(char c, int fd);
int	ft_dputstr_fd_error(char *s, int fd);
int	ft_dputnbr_fd_error(int n, int fd);

#endif
