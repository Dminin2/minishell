/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:31:13 by aomatsud          #+#    #+#             */
/*   Updated: 2025/08/26 15:01:07 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nbrlen(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	num;
	char	buf[12];
	int		len;
	int		i;

	num = n;
	if (num == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	len = nbrlen(num);
	if (num < 0)
	{
		buf[0] = '-';
		num *= -1;
	}
	i = len - 1;
	while (num)
	{
		buf[i] = num % 10 + '0';
		i--;
		num /= 10;
	}
	write(fd, buf, len);
}
