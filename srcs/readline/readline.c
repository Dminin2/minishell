/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:50:28 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/19 13:34:33 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	*get_command_line(t_minishell *minishell)
{
	t_status	status;
	t_input		*input;

	input = ft_calloc(1, sizeof(t_input));
	if (!input)
	{
		print_error_msg("malloc", ERR_MALLOC);
		return (NULL);
	}
	if (isatty(STDIN_FILENO))
	{
		if (isatty(STDERR_FILENO))
			input->line = readline("minishell$ ");
		else
			input->line = readline("");
		if (g_sig == SIGINT)
		{
			minishell->last_status = 130;
			g_sig = 0;
		}
		if (input->line && input->line[0])
			add_history(input->line);
		input->is_eof = 0;
		status = SUCCESS;
	}
	else
		status = gnl_and_remove_new_line(input);
	if (status != SUCCESS)
	{
		free_input(input);
		input = NULL;
		minishell->last_status = 1;
	}
	return (input);
}
