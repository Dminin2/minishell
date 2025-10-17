/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:50:28 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/17 03:13:15 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	get_command_line(t_minishell *minishell, char **line)
{
	t_status	status;

	if (isatty(STDIN_FILENO))
	{
		if (isatty(STDERR_FILENO))
			*line = readline("minishell$ ");
		else
			*line = readline("");
		if (g_sig == SIGINT)
		{
			minishell->last_status = 130;
			g_sig = 0;
		}
		if (*line && *line[0])
			add_history(*line);
		status = SUCCESS;
	}
	else
		status = gnl_and_remove_new_line(line);
	if (status != SUCCESS)
		minishell->last_status = 1;
	return (status);
}
