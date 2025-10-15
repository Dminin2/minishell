/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprint_char_string_percent.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:43:02 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/16 00:53:01 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	dprint_char(int fd, int n)
{
	char	c;

	c = (char)n;
	if (ft_dputchar_fd_error(c, fd) == -1)
		return (-1);
	return (1);
}

int	dprint_string(int fd, char *str)
{
	if (!str)
	{
		if (ft_dputstr_fd_error("(null)", fd) == -1)
			return (-1);
		return (6);
	}
	if (ft_dputstr_fd_error(str, fd) == -1)
		return (-1);
	return (ft_strlen(str));
}

int	dprint_percent(int fd)
{
	if (ft_dputchar_fd_error('%', fd) == -1)
		return (-1);
	return (1);
}
