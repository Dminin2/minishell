/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprint_hexadecimal_buf.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:00:00 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/23 00:00:00 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf_buf.h"

static void	buf_puthex_uppercase(t_dprintf_buf *buffer, unsigned long n)
{
	char	*hex;

	hex = "0123456789ABCDEF";
	if (n >= 16)
		buf_puthex_uppercase(buffer, n / 16);
	buf_putchar(buffer, hex[n % 16]);
}

static void	buf_puthex_lowercase(t_dprintf_buf *buffer, unsigned long n)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n >= 16)
		buf_puthex_lowercase(buffer, n / 16);
	buf_putchar(buffer, hex[n % 16]);
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

int	dprint_hexadecimal_buf(t_dprintf_buf *buffer, unsigned int nbr,
		int hex_case)
{
	int	len;

	len = count_hex_digits((unsigned long)nbr);
	if (hex_case == -1)
		buf_puthex_lowercase(buffer, (unsigned long)nbr);
	else if (hex_case == 1)
		buf_puthex_uppercase(buffer, (unsigned long)nbr);
	return (len);
}

int	dprint_pointer_buf(t_dprintf_buf *buffer, void *ptr)
{
	unsigned long	mem;
	int				len;

	if (!ptr)
		return (buf_putstr(buffer, "(nil)", 5));
	mem = (unsigned long)ptr;
	buf_putstr(buffer, "0x", 2);
	len = count_hex_digits(mem);
	buf_puthex_lowercase(buffer, mem);
	return (2 + len);
}
