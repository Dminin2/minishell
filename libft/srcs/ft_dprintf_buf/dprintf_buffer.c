/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:00:00 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/23 00:00:00 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf_buf.h"

void	buf_init(t_dprintf_buf *buffer, int fd)
{
	buffer->pos = 0;
	buffer->fd = fd;
}

int	buf_flush(t_dprintf_buf *buffer)
{
	if (buffer->pos == 0)
		return (0);
	if (write(buffer->fd, buffer->buf, buffer->pos) == -1)
		return (-1);
	buffer->pos = 0;
	return (0);
}

int	buf_putchar(t_dprintf_buf *buffer, char c)
{
	buffer->buf[buffer->pos++] = c;
	return (1);
}

int	buf_putstr(t_dprintf_buf *buffer, char *str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		buffer->buf[buffer->pos++] = str[i];
		i++;
	}
	return (len);
}
