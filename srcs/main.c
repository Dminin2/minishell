/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:54:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/08 12:46:02 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_init(t_minishell *minishell, char **envp)
{
	if (isatty(STDIN_FILENO))
		set_signal_interactive();
	else
		set_signal_noninteractive();
	minishell->should_exit = 0;
	minishell->last_status = 0;
	minishell->env_lst = env_init(minishell, envp);
	if (!minishell->env_lst)
		exit(2);
	rl_outstream = stderr;
}

void	reader_loop(t_minishell *minishell)
{
	t_list			*token_lst;
	t_pipeline_ir	*pipeline_ir;
	t_pipeline		*pipeline;
	t_input			*input;

	while (!minishell->should_exit)
	{
		input = get_command_line(minishell);
		if (!input)
			continue ;
		token_lst = tokenize(minishell, input);
		free_input(input);
		if (!token_lst)
			continue ;
		pipeline_ir = parse(minishell, token_lst);
		ft_lstclear(&token_lst, &free_token_wrapper);
		if (!pipeline_ir)
			continue ;
		pipeline = expand(minishell, pipeline_ir);
		free_pipeline_ir(pipeline_ir);
		if (!pipeline)
			continue ;
		execute(minishell, pipeline);
	}
}

void	minishell_cleanup(t_minishell *minishell)
{
	rl_clear_history();
	ft_lstclear(&(minishell->env_lst), free_env_wrapper);
	free(minishell->cwd);
	if (!isatty(STDIN_FILENO))
		get_next_line(-1);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	minishell_init(&minishell, envp);
	reader_loop(&minishell);
	minishell_cleanup(&minishell);
	return (minishell.last_status);
}
