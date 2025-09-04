/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:54:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/04 21:56:08 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_list		*lst;
	t_pipeline	*pipeline;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = get_command_line();
		//入力終了
		if (!line)
			break ;
		lst = tokenize(line);
		free(line);
		if (!lst) // malloc失敗もしくはsytax error
			continue ;
		// debug用残しておきます
		// print_lst(lst);
		pipeline = parse(lst);
		ft_lstclear(&lst, &free_token_wrapper);
		if (!pipeline) // malloc失敗もしくはsytax error
			continue ;
		// debug用残しておきます
		// print_pipeline(pipeline);
		if (read_heredoc(pipeline->cmd_lst) == FAILURE)
		{
			close_heredoc(pipeline->cmd_lst);
			free_pipeline(pipeline);
			continue ;
		}
		//子プロセスにコマンドを実行させる
		//パイプ作ってないので最初のコマンドしか実行できません
		child_process(pipeline, envp);
		// free_args(cmd->args);
		// free(cmd);
	}
	return (0);
}
