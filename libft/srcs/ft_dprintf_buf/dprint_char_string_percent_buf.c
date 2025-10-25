/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprint_char_string_percent_buf.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 00:00:00 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/23 00:00:00 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf_buf.h"

int	dprint_char_buf(t_dprintf_buf *buffer, int n)
{
	char	c;

	c = (char)n;
	return (buf_putchar(buffer, c));
}

int	dprint_string_buf(t_dprintf_buf *buffer, char *str)
{
	int	len;

	if (!str)
		return (buf_putstr(buffer, "(null)", 6));
	len = ft_strlen(str);
	return (buf_putstr(buffer, str, len));
}

int	dprint_percent_buf(t_dprintf_buf *buffer)
{
	return (buf_putchar(buffer, '%'));
}
