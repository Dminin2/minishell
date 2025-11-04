/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:54:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/04 16:59:19 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef DEBUG
int		g_fd = -1;
#endif

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
		exit(1);
	rl_outstream = stderr;
#ifdef DEBUG
	g_fd = open("playground/log", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC,
			0644);
	if (g_fd < 0)
	{
		printf("log file error\n");
		exit(1);
	}
	print_env_lst(minishell->env_lst, g_fd);
#endif
}

void	reader_loop(t_minishell *minishell)
{
	t_list			*token_lst;
	t_pipeline_ir	*pipeline_ir;
	t_pipeline		*pipeline;
	t_input			input;

	while (!minishell->should_exit)
	{
#ifdef DEBUG
		print_status(minishell->last_status, g_fd);
#endif
		if (get_command_line(minishell, &input) != SUCCESS)
			continue ;
		if (!(input.line))
		{
			if (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
				ft_dprintf(STDERR_FILENO, "exit\n");
			break ;
		}
#ifdef DEBUG
		print_input(&input, g_fd);
#endif
		token_lst = tokenize(minishell, &input);
		free(input.line);
		if (!token_lst)
			continue ;
#ifdef DEBUG
		print_token(token_lst, g_fd);
#endif
		pipeline_ir = parse(minishell, token_lst);
		ft_lstclear(&token_lst, &free_token_wrapper);
		if (!pipeline_ir)
			continue ;
#ifdef DEBUG
		print_pipeline_ir(pipeline_ir, g_fd);
#endif
		pipeline = expand(minishell, pipeline_ir);
		if (!pipeline)
		{
			free_pipeline_ir(pipeline_ir);
			continue ;
		}
		else
			free_pipeline_ir_after_expand(pipeline_ir);
#ifdef DEBUG
		print_pipeline(pipeline, g_fd);
#endif
		execute(minishell, pipeline);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	minishell_init(&minishell, envp);
	reader_loop(&minishell);
	rl_clear_history();
	ft_lstclear(&(minishell.env_lst), free_env_wrapper);
	free(minishell.cwd);
#ifdef DEBUG
	close(g_fd);
#endif
	return (minishell.last_status);
}
