/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:20:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/02 20:36:57 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_format(const char c, va_list *args)
{
	if (c == 'c')
		return (print_char(va_arg(*args, int)));
	else if (c == 's')
		return (print_string(va_arg(*args, char *)));
	else if (c == 'p')
		return (print_pointer(va_arg(*args, void *)));
	else if (c == 'd' || c == 'i')
		return (print_decimal(va_arg(*args, int)));
	else if (c == 'u')
		return (print_unsigned_decimal(va_arg(*args, unsigned int)));
	else if (c == 'x')
		return (print_hexadecimal(va_arg(*args, unsigned int), -1));
	else if (c == 'X')
		return (print_hexadecimal(va_arg(*args, unsigned int), 1));
	else if (c == '%')
		return (print_percent());
	else
		return (-1);
}

static int	loop_format(const char *format, va_list *args)
{
	int	i;
	int	len;
	int	result;

	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%')
			result = handle_format(format[++i], args);
		else
		{
			if (ft_putchar_fd_error(format[i], 1) == -1)
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

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	if (!format)
		return (-1);
	va_start(args, format);
	len = loop_format(format, &args);
	va_end(args);
	return (len);
}
