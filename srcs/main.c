/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:54:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/12 12:47:00 by aomatsud         ###   ########.fr       */
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
		if (!line)
			break ;
		lst = tokenize(line);
		free(line);
		if (!lst)
			continue ;
#ifdef DEBUG
		print_token(lst);
#endif
		pipeline = parse(lst);
		ft_lstclear(&lst, &free_token_wrapper);
		if (!pipeline)
			continue ;
#ifdef DEBUG
		print_pipeline(pipeline);
#endif
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
