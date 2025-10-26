/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprint_char_string_percent_buf.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 10:32:51 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/26 10:32:53 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf_buf.h"

int	dprint_char_buf(t_dprintf_buf *buffer, int n)
{
	char	c;

	if (buffer->pos + 1 > PIPE_BUF)
	{
		if (buf_flush(buffer) == -1)
			return (-1);
	}
	c = (char)n;
	return (buf_putchar(buffer, c));
}

int	dprint_string_buf(t_dprintf_buf *buffer, char *str)
{
	int	len;

	if (!str)
	{
		len = 6;
		str = "(null)";
	}
	else
		len = ft_strlen(str);
	if (len > PIPE_BUF)
	{
		if (buf_flush(buffer) == -1)
			return (-1);
		if (write(buffer->fd, str, len) == -1)
			return (-1);
		return (len);
	}
	if (buffer->pos + len > PIPE_BUF)
	{
		if (buf_flush(buffer) == -1)
			return (-1);
	}
	return (buf_putstr(buffer, str, len));
}

int	dprint_percent_buf(t_dprintf_buf *buffer)
{
	if (buffer->pos + 1 > PIPE_BUF)
	{
		if (buf_flush(buffer) == -1)
			return (-1);
	}
	return (buf_putchar(buffer, '%'));
}
