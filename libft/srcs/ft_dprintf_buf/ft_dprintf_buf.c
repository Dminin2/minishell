/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_buf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:00:00 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/23 00:00:00 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf_buf.h"

static int	handle_format_buf(t_dprintf_buf *buffer, const char c,
		va_list *args)
{
	if (c == 'c')
		return (dprint_char_buf(buffer, va_arg(*args, int)));
	else if (c == 's')
		return (dprint_string_buf(buffer, va_arg(*args, char *)));
	else if (c == 'p')
		return (dprint_pointer_buf(buffer, va_arg(*args, void *)));
	else if (c == 'd' || c == 'i')
		return (dprint_decimal_buf(buffer, va_arg(*args, int)));
	else if (c == 'u')
		return (dprint_unsigned_decimal_buf(buffer, va_arg(*args,
					unsigned int)));
	else if (c == 'x')
		return (dprint_hexadecimal_buf(buffer, va_arg(*args, unsigned int),
				-1));
	else if (c == 'X')
		return (dprint_hexadecimal_buf(buffer, va_arg(*args, unsigned int), 1));
	else if (c == '%')
		return (dprint_percent_buf(buffer));
	else
		return (-1);
}

static int	loop_format_buf(t_dprintf_buf *buffer, const char *format,
		va_list *args)
{
	int	i;
	int	len;
	int	result;

	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%')
			result = handle_format_buf(buffer, format[++i], args);
		else
		{
			if (buffer->pos + 1 > PIPE_BUF)
			{
				if (buf_flush(buffer) == -1)
					return (-1);
			}
			result = buf_putchar(buffer, format[i]);
		}
		if (result == -1)
			return (-1);
		i++;
		len += result;
	}
	return (len);
}

int	ft_dprintf_buf(int fd, const char *format, ...)
{
	va_list			args;
	int				len;
	t_dprintf_buf	buffer;

	if (!format)
		return (-1);
	if (fd < 0)
		return (-1);
	buf_init(&buffer, fd);
	va_start(args, format);
	len = loop_format_buf(&buffer, format, &args);
	va_end(args);
	if (len == -1)
		return (-1);
	if (buf_flush(&buffer) == -1)
		return (-1);
	return (len);
}
