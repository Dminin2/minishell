/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:54:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/26 21:38:18 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_list			*token_lst;
	t_pipeline_ir	*pipeline_ir;
	t_minishell		minishell;
	t_pipeline		*pipeline;

	(void)argc;
	(void)argv;
	minishell.last_status = 0;
	minishell.env_lst = env_init(envp);
	if (!minishell.env_lst)
		exit(1);
#ifdef DEBUG
	print_env_lst(minishell.env_lst);
#endif
	while (1)
	{
		line = get_command_line();
		if (!line)
			break ;
		token_lst = tokenize(line);
		free(line);
		if (!token_lst)
			continue ;
#ifdef DEBUG
		print_token(token_lst);
#endif
		pipeline_ir = parse(token_lst);
		ft_lstclear(&token_lst, &free_token_wrapper);
		if (!pipeline_ir)
			continue ;
#ifdef DEBUG
		print_pipeline_ir(pipeline_ir);
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
		print_pipeline(pipeline);
#endif
		free_pipeline(pipeline);
		// executeできる状態じゃないのでコメントアウト
		// if (read_heredoc(pipeline->cmd_lst) == FAILURE)
		// {
		// 	close_heredoc(pipeline->cmd_lst);
		// 	free_pipeline(pipeline);
		// 	continue ;
		// }
		// child_process(pipeline, envp);
#ifdef DEBUG
		print_status(minishell.last_status);
#endif
	}
	ft_lstclear(&(minishell.env_lst), free_env_wrapper);
	return (0);
}
