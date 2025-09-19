/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:54:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/16 11:50:58 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_list			*token_lst;
	t_pipeline_ir	*pipeline_ir;

	// t_pipeline		*pipeline;
	(void)argc;
	(void)argv;
	(void)envp;
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
		free_pipeline_ir(pipeline_ir);
		// executeできる状態じゃないのでコメントアウト
		// if (read_heredoc(pipeline->cmd_lst) == FAILURE)
		// {
		// 	close_heredoc(pipeline->cmd_lst);
		// 	free_pipeline(pipeline);
		// 	continue ;
		// }
		// child_process(pipeline, envp);
	}
	return (0);
}
