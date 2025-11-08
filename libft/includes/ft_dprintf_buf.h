/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_buf.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:00:00 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/08 12:15:34 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_BUF_H
# define FT_DPRINTF_BUF_H

# include "libft.h"
# include <limits.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_dprintf_buf
{
	char	buf[PIPE_BUF];
	int		pos;
	int		fd;
}			t_dprintf_buf;

int			ft_dprintf_buf(int fd, const char *format, ...);

int			dprint_char_buf(t_dprintf_buf *buffer, int n);
int			dprint_string_buf(t_dprintf_buf *buffer, char *str);
int			dprint_percent_buf(t_dprintf_buf *buffer);
int			dprint_pointer_buf(t_dprintf_buf *buffer, void *ptr);
int			dprint_decimal_buf(t_dprintf_buf *buffer, int nbr);
int			dprint_unsigned_decimal_buf(t_dprintf_buf *buffer,
				unsigned int nbr);
int			dprint_hexadecimal_buf(t_dprintf_buf *buffer, unsigned int nbr,
				int hex_case);

void		buf_init(t_dprintf_buf *buffer, int fd);
int			buf_flush(t_dprintf_buf *buffer);
int			buf_putchar(t_dprintf_buf *buffer, char c);
int			buf_putstr(t_dprintf_buf *buffer, char *str, int len);
void		buf_putnbr_unsigned(t_dprintf_buf *buffer, unsigned int n);

#endif
