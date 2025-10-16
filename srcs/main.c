/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:54:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/15 22:57:10 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef DEBUG
int	g_fd = -1;
#endif

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_list			*token_lst;
	t_pipeline_ir	*pipeline_ir;
	t_minishell		minishell;
	t_pipeline		*pipeline;
	t_status		status;

	(void)argc;
	(void)argv;
	minishell.should_exit = 0;
	minishell.last_status = 0;
	minishell.env_lst = env_init(&minishell, envp);
	if (!minishell.env_lst)
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
	print_env_lst(minishell.env_lst, g_fd);
#endif
	while (1)
	{
#ifdef DEBUG
		print_status(minishell.last_status, g_fd);
#endif
		status = get_command_line(&minishell, &line);
		if (status != SUCCESS)
			continue ;
		if (!line)
			break ;
#ifdef DEBUG
		print_line(line, g_fd);
#endif
		token_lst = tokenize(&minishell, line);
		free(line);
		if (!token_lst)
			continue ;
#ifdef DEBUG
		print_token(token_lst, g_fd);
#endif
		pipeline_ir = parse(&minishell, token_lst);
		ft_lstclear(&token_lst, &free_token_wrapper);
		if (!pipeline_ir)
			continue ;
#ifdef DEBUG
		print_pipeline_ir(pipeline_ir, g_fd);
#endif
		pipeline = expand(&minishell, pipeline_ir);
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
		if (read_heredoc(&minishell, pipeline) == FAILURE)
			continue ;
		execute(&minishell, pipeline);
		if (minishell.should_exit)
			break ;
	}
	rl_clear_history();
	ft_lstclear(&(minishell.env_lst), free_env_wrapper);
#ifdef DEBUG
	close(g_fd);
#endif
	return (minishell.last_status);
}
