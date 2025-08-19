/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_decimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:33:35 by aomatsud          #+#    #+#             */
/*   Updated: 2025/05/16 00:23:34 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_unsigned_error(unsigned int n)
{
	char	c;

	if (n >= 10)
	{
		if (ft_putnbr_unsigned_error(n / 10) == -1)
			return (-1);
	}
	c = n % 10 + '0';
	if (write(1, &c, 1) == -1)
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

int	print_decimal(int nbr)
{
	if (ft_putnbr_fd_error(nbr, 1) == -1)
		return (-1);
	return (count_decimal_digits(nbr));
}

int	print_unsigned_decimal(unsigned int nbr)
{
	if (ft_putnbr_unsigned_error(nbr) == -1)
		return (-1);
	return (count_unsigned_decimal_digits(nbr));
}
