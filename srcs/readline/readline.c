/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:50:28 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/09 15:19:14 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command_line(void)
{
	char	*line;

	if (isatty(STDERR_FILENO) && isatty(STDIN_FILENO))
		ft_putstr_fd("minishell$ ", STDERR_FILENO);
	line = readline("");
	if (line)
		add_history(line);
	return (line);
}
