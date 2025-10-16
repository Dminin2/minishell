/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprint_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:33:35 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/16 12:56:59 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	ft_dputnbr_unsigned_fd_error(unsigned int n, int fd)
{
	char	c;

	if (n >= 10)
	{
		if (ft_dputnbr_unsigned_fd_error(n / 10, fd) == -1)
			return (-1);
	}
	c = n % 10 + '0';
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (0);
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

int	dprint_decimal(int fd, int nbr)
{
	if (ft_dputnbr_fd_error(nbr, fd) == -1)
		return (-1);
	return (count_decimal_digits(nbr));
}

int	dprint_unsigned_decimal(int fd, unsigned int nbr)
{
	if (ft_dputnbr_unsigned_fd_error(nbr, fd) == -1)
		return (-1);
	return (count_unsigned_decimal_digits(nbr));
}
