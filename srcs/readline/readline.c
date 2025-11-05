/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:50:28 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/04 21:50:20 by hmaruyam         ###   ########.fr       */
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

static char	*create_prompt(t_minishell *minishell)
{
	char	*prompt;
	char	*tmp;
	char	*cwd;
	char	*part1;

	cwd = minishell->cwd;
	if (!cwd)
		cwd = ".";
	if (minishell->last_status == 0)
		part1 = PROMPT_PART1_SUCCESS;
	else
		part1 = PROMPT_PART1_ERROR;
	tmp = ft_strjoin(part1, cwd);
	if (!tmp)
		return (NULL);
	prompt = ft_strjoin(tmp, PROMPT_PART2);
	free(tmp);
	return (prompt);
}

t_status	get_command_line(t_minishell *minishell, t_input *input)
{
	t_status	status;
	char		*prompt;

	if (isatty(STDIN_FILENO))
	{
		if (isatty(STDERR_FILENO))
		{
			prompt = create_prompt(minishell);
			if (!prompt)
			{
				print_error_msg("malloc", ERR_MALLOC);
				return (ERR_MALLOC);
			}
			input->line = readline(prompt);
			free(prompt);
		}
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
