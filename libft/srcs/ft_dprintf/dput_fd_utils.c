/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dput_fd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 00:10:56 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/16 00:57:18 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputchar_fd_error(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (0);
}

int	ft_dputstr_fd_error(char *s, int fd)
{
	if (!s)
		return (-1);
	if (write(fd, s, ft_strlen(s)) == -1)
		return (-1);
	return (0);
}

int	ft_dputnbr_fd_error(int n, int fd)
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
		if (ft_dputnbr_fd_error(num / 10, fd) == -1)
			return (-1);
	c = num % 10 + '0';
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (0);
}
