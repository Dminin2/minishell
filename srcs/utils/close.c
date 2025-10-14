/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 20:27:22 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/13 17:21:47 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_redir_lst(t_list *redir_lst)
{
	t_redir	*redir;

	while (redir_lst)
	{
		redir = redir_lst->content;
		if (redir->fd_hd >= 0)
		{
			close(redir->fd_hd);
			redir->fd_hd = -1;
		}
		redir_lst = redir_lst->next;
	}
}

void	close_heredoc(t_list *cmd_lst)
{
	t_cmd	*cmd;

	while (cmd_lst)
	{
		cmd = cmd_lst->content;
		if (cmd->redir_lst)
			loop_redir_lst(cmd->redir_lst);
		cmd_lst = cmd_lst->next;
	}
}

void	close_simple_pipe(int *pipe)
{
	if (!pipe)
		return ;
	if (pipe[0] >= 0)
		close(pipe[0]);
	if (pipe[1] >= 0)
		close(pipe[1]);
	pipe[0] = -1;
	pipe[1] = -1;
}

void	close_pipes(int **pipes, int n)
{
	int	i;

	i = 0;
	if (pipes)
	{
		while (i < n)
		{
			close_simple_pipe(pipes[i]);
			i++;
		}
	}
}
