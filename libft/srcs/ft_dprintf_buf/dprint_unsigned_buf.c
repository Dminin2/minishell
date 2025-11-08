/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprint_unsigned_buf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 01:00:51 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/08 12:15:19 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf_buf.h"

static int	count_unsigned_decimal_digits(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

int	dprint_unsigned_decimal_buf(t_dprintf_buf *buffer, unsigned int nbr)
{
	int	len;

	len = count_unsigned_decimal_digits(nbr);
	if (buffer->pos + len >= PIPE_BUF)
	{
		if (buf_flush(buffer) == -1)
			return (-1);
	}
	buf_putnbr_unsigned(buffer, nbr);
	return (len);
}
