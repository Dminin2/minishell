/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprint_decimal_buf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:00:00 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/23 00:00:00 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf_buf.h"

static void	buf_putnbr_unsigned(t_dprintf_buf *buffer, unsigned int n)
{
	char	c;

	if (n >= 10)
		buf_putnbr_unsigned(buffer, n / 10);
	c = n % 10 + '0';
	buf_putchar(buffer, c);
}

static void	buf_putnbr(t_dprintf_buf *buffer, int nbr)
{
	long	num;

	num = nbr;
	if (num < 0)
	{
		buf_putchar(buffer, '-');
		num *= -1;
	}
	buf_putnbr_unsigned(buffer, (unsigned int)num);
}

static int	count_decimal_digits(int nbr)
{
	int		len;
	long	n;

	len = 0;
	n = nbr;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

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

int	dprint_decimal_buf(t_dprintf_buf *buffer, int nbr)
{
	int	len;

	len = count_decimal_digits(nbr);
	if (buffer->pos + len > PIPE_BUF)
	{
		if (buf_flush(buffer) == -1)
			return (-1);
	}
	buf_putnbr(buffer, nbr);
	return (len);
}

int	dprint_unsigned_decimal_buf(t_dprintf_buf *buffer, unsigned int nbr)
{
	int	len;

	len = count_unsigned_decimal_digits(nbr);
	if (buffer->pos + len > PIPE_BUF)
	{
		if (buf_flush(buffer) == -1)
			return (-1);
	}
	buf_putnbr_unsigned(buffer, nbr);
	return (len);
}
