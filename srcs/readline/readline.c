/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:50:28 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/27 12:46:35 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_working_history(char *line)
{
	int	i;
	int	is_blank;

	i = 0;
	is_blank = 1;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			is_blank = 0;
			break ;
		}
		i++;
	}
	if (!is_blank || line[0] != ' ')
		add_history(line);
}

t_status	get_command_line(t_minishell *minishell, t_input *input)
{
	t_status	status;

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
			handle_working_history(input->line);
		input->is_eof = 0;
		status = SUCCESS;
	}
	else
		status = gnl_and_remove_new_line(input);
	if (status != SUCCESS)
	{
		print_error_msg("malloc", status);
		minishell->last_status = 1;
	}
	return (status);
}
