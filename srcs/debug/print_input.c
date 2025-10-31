/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:50:29 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/29 22:12:25 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_input(t_input *input, int fd)
{
	ft_dprintf(fd, "***** input *****\n");
	if (input->is_eof)
		ft_dprintf(fd, "is_eof : true\n");
	else
		ft_dprintf(fd, "is_eof : false\n");
	ft_dprintf(fd, "line   : %s\n\n", input->line);
}
