/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:58:42 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/19 13:34:47 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	gnl_and_remove_new_line(t_input *input)
{
	int			i;
	t_status	status;
	char		*line;

	status = SUCCESS;
	line = get_next_line(STDIN_FILENO);
	if (line)
	{
		i = 0;
		while (line[i] && line[i] != '\n')
			i++;
		if (line[i] == '\n')
		{
			input->line = ft_substr(line, 0, i);
			if (!(input->line))
				status = ERR_MALLOC;
			free(line);
			input->is_eof = 0;
		}
		else
		{
			input->line = line;
			input->is_eof = 1;
		}
	}
	return (status);
}
