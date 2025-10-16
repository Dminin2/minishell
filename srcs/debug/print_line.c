/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:50:29 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/16 01:52:44 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_line(char *line, int fd)
{
	ft_dprintf(fd, "***** line *****\n");
	ft_dprintf(fd, "%s\n\n", line);
}
