/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char_string_percent.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:43:02 by aomatsud          #+#    #+#             */
/*   Updated: 2025/05/21 21:52:30 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(int n)
{
	char	c;

	c = (char)n;
	if (ft_putchar_fd_error(c, 1) == -1)
		return (-1);
	return (1);
}

int	print_string(char *str)
{
	if (!str)
	{
		if (ft_putstr_fd_error("(null)", 1) == -1)
			return (-1);
		return (6);
	}
	if (ft_putstr_fd_error(str, 1) == -1)
		return (-1);
	return (ft_strlen(str));
}

int	print_percent(void)
{
	if (ft_putchar_fd_error('%', 1) == -1)
		return (-1);
	return (1);
}
