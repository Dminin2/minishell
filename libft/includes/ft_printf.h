/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:24:04 by aomatsud          #+#    #+#             */
/*   Updated: 2025/07/24 11:12:40 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	print_char(int n);
int	print_string(char *str);
int	print_percent(void);
int	print_pointer(void *ptr);
int	print_decimal(int nbr);
int	print_unsigned_decimal(unsigned int nbr);
int	print_hexadecimal(unsigned int nbr, int hex_case);

int	ft_putchar_fd_error(char c, int fd);
int	ft_putstr_fd_error(char *s, int fd);
int	ft_putnbr_fd_error(int n, int fd);

#endif
