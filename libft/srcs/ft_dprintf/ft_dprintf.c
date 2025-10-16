/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:20:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/16 01:02:29 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	handle_format_fd(int fd, const char c, va_list *args)
{
	if (c == 'c')
		return (dprint_char(fd, va_arg(*args, int)));
	else if (c == 's')
		return (dprint_string(fd, va_arg(*args, char *)));
	else if (c == 'p')
		return (dprint_pointer(fd, va_arg(*args, void *)));
	else if (c == 'd' || c == 'i')
		return (dprint_decimal(fd, va_arg(*args, int)));
	else if (c == 'u')
		return (dprint_unsigned_decimal(fd, va_arg(*args, unsigned int)));
	else if (c == 'x')
		return (dprint_hexadecimal(fd, va_arg(*args, unsigned int), -1));
	else if (c == 'X')
		return (dprint_hexadecimal(fd, va_arg(*args, unsigned int), 1));
	else if (c == '%')
		return (dprint_percent(fd));
	else
		return (-1);
}

static int	loop_format_fd(int fd, const char *format, va_list *args)
{
	int	i;
	int	len;
	int	result;

	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%')
			result = handle_format_fd(fd, format[++i], args);
		else
		{
			if (ft_dputchar_fd_error(format[i], fd) == -1)
				result = -1;
			else
				result = 1;
		}
		if (result == -1)
			return (-1);
		i++;
		len += result;
	}
	return (len);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		len;

	if (!format)
		return (-1);
	if (fd < 0)
		return (-1);
	va_start(args, format);
	len = loop_format_fd(fd, format, &args);
	va_end(args);
	return (len);
}
