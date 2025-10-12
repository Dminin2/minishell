/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:50:28 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/12 23:35:29 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gnl_and_remove_new_line(void)
{
	char	*line;
	int		i;
	char	*removed_new_line;

	line = get_next_line(STDIN_FILENO);
	if (line)
	{
		i = 0;
		while (line[i] != '\n')
			i++;
		if (line[i] == '\n')
		{
			removed_new_line = ft_substr(line, 0, i);
			free(line);
			line = removed_new_line;
		}
	}
	return (line);
}

char	*get_command_line(void)
{
	char	*line;

	if (isatty(STDERR_FILENO) && isatty(STDIN_FILENO))
		ft_putstr_fd("minishell$ ", STDERR_FILENO);
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		line = readline("");
	else
		line = gnl_and_remove_new_line();
	if (line)
		add_history(line);
	return (line);
}
