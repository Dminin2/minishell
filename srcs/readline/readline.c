/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:50:28 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/15 22:11:13 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	gnl_and_remove_new_line(char **line)
{
	int			i;
	char		*removed_new_line;
	t_status	status;

	status = SUCCESS;
	*line = get_next_line(STDIN_FILENO);
	if (*line)
	{
		i = 0;
		while ((*line)[i] && (*line)[i] != '\n')
			i++;
		if ((*line)[i] == '\n')
		{
			removed_new_line = ft_substr(*line, 0, i);
			if (!removed_new_line)
			{
				print_error_msg("malloc", ERR_MALLOC);
				status = ERR_MALLOC;
			}
			free(*line);
			*line = removed_new_line;
		}
	}
	return (status);
}

t_status	get_command_line(char **line)
{
	t_status	status;

	if (isatty(STDIN_FILENO))
	{
		if (isatty(STDERR_FILENO))
			*line = readline("minishell$ ");
		else
			*line = readline("");
		status = SUCCESS;
		if (*line)
			add_history(*line);
	}
	else
		status = gnl_and_remove_new_line(line);
	return (status);
}
