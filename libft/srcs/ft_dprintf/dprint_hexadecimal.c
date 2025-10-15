/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprint_hexadecimal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:47:21 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/16 00:54:31 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	ft_dputhex_uppercase_fd(unsigned long n, int fd)
{
	char	*hex;

	hex = "0123456789ABCDEF";
	if (n >= 16)
	{
		if (ft_dputhex_uppercase_fd(n / 16, fd) == -1)
			return (-1);
	}
	if (write(fd, &hex[n % 16], 1) == -1)
		return (-1);
	return (0);
}

static int	ft_dputhex_lowercase_fd(unsigned long n, int fd)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n >= 16)
	{
		if (ft_dputhex_lowercase_fd(n / 16, fd) == -1)
			return (-1);
	}
	if (write(fd, &hex[n % 16], 1) == -1)
		return (-1);
	return (0);
}

static int	count_hex_digits(unsigned long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		len++;
		n /= 16;
	}
	return (len);
}

int	dprint_hexadecimal(int fd, unsigned int nbr, int hex_case)
{
	if (hex_case == -1)
	{
		if (ft_dputhex_lowercase_fd((unsigned long)nbr, fd) == -1)
			return (-1);
		return (count_hex_digits((unsigned long)nbr));
	}
	else if (hex_case == 1)
	{
		if (ft_dputhex_uppercase_fd((unsigned long)nbr, fd) == -1)
			return (-1);
		return (count_hex_digits((unsigned long)nbr));
	}
	else
		return (-1);
}

int	dprint_pointer(int fd, void *ptr)
{
	unsigned long	mem;

	if (!ptr)
	{
		if (write(fd, "(nil)", 5) == -1)
			return (-1);
		return (5);
	}
	mem = (unsigned long)ptr;
	if (write(fd, "0x", 2) == -1)
		return (-1);
	if (ft_dputhex_lowercase_fd(mem, fd) == -1)
		return (-1);
	return (2 + count_hex_digits(mem));
}
