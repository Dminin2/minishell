/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:20:38 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/11 20:49:59 by aomatsud         ###   ########.fr       */
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
	while (1)
	{
		line = get_command_line();
		if (!line)
			break ;
		lst = tokenize(line);
		free(line);
		if (!lst)
			continue ;
		print_token(lst);
		pipeline = parse(lst);
		ft_lstclear(&lst, &free_token_wrapper);
		if (!pipeline)
			continue ;
		print_pipeline(pipeline);
		if (read_heredoc(pipeline->cmd_lst) == FAILURE)
		{
			close_heredoc(pipeline->cmd_lst);
			free_pipeline(pipeline);
			continue ;
		}
		child_process(pipeline, envp);
	}
	return (0);
}
