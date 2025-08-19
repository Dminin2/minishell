/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_fd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:10:56 by aomatsud          #+#    #+#             */
/*   Updated: 2025/05/21 21:52:34 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_fd_error(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (0);
}

int	ft_putstr_fd_error(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (write(fd, &s[i], 1) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_putnbr_fd_error(int n, int fd)
{
	long	num;
	char	c;

	num = n;
	if (num < 0)
	{
		if (write(fd, "-", 1) == -1)
			return (-1);
		num *= -1;
	}
	if (num >= 10)
		if (ft_putnbr_fd_error(num / 10, fd) == -1)
			return (-1);
	c = num % 10 + '0';
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (0);
}
