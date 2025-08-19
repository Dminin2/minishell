/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexadecimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:47:21 by aomatsud          #+#    #+#             */
/*   Updated: 2025/05/16 00:22:26 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_puthex_uppercase(unsigned long n)
{
	char	*hex;

	hex = "0123456789ABCDEF";
	if (n >= 16)
	{
		if (ft_puthex_uppercase(n / 16) == -1)
			return (-1);
	}
	if (write(1, &hex[n % 16], 1) == -1)
		return (-1);
	return (0);
}

static int	ft_puthex_lowercase(unsigned long n)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n >= 16)
	{
		if (ft_puthex_lowercase(n / 16) == -1)
			return (-1);
	}
	if (write(1, &hex[n % 16], 1) == -1)
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

int	print_hexadecimal(unsigned int nbr, int hex_case)
{
	if (hex_case == -1)
	{
		if (ft_puthex_lowercase((unsigned long)nbr) == -1)
			return (-1);
		return (count_hex_digits((unsigned long)nbr));
	}
	else if (hex_case == 1)
	{
		if (ft_puthex_uppercase((unsigned long)nbr) == -1)
			return (-1);
		return (count_hex_digits((unsigned long)nbr));
	}
	else
		return (-1);
}

int	print_pointer(void *ptr)
{
	unsigned long	mem;

	if (!ptr)
	{
		if (write(1, "(nil)", 5) == -1)
			return (-1);
		return (5);
	}
	mem = (unsigned long)ptr;
	if (write(1, "0x", 2) == -1)
		return (-1);
	if (ft_puthex_lowercase(mem) == -1)
		return (-1);
	return (2 + count_hex_digits(mem));
}
