/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:13:47 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/07 00:49:00 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	dup_if_needed(int *saved_fd, int target_fd)
{
	if (*saved_fd == -1)
	{
		*saved_fd = dup(target_fd);
		if (*saved_fd == -1)
			return (ERR_DUP);
	}
	return (SUCCESS);
}

t_status	save_stdio_fd(t_list *redir_lst, int *saved)
{
	t_redir		*redir;
	t_status	status;

	while (redir_lst)
	{
		redir = redir_lst->content;
		if (redir->type == R_IN || redir->type == R_HEREDOC)
			status = dup_if_needed(&saved[0], STDIN_FILENO);
		else
			status = dup_if_needed(&saved[1], STDOUT_FILENO);
		if (status == ERR_DUP)
			return (ERR_DUP);
		redir_lst = redir_lst->next;
	}
	return (SUCCESS);
}

t_status	restore_stdio_fd(int *saved)
{
	if (saved[0] != -1)
	{
		if (dup2(saved[0], STDIN_FILENO) == -1)
		{
			close(saved[0]);
			if (saved[1] != -1)
				close(saved[1]);
			return (ERR_DUP);
		}
		close(saved[0]);
		saved[0] = -1;
	}
	if (saved[1] != -1)
	{
		if (dup2(saved[1], STDOUT_FILENO) == -1)
		{
			close(saved[1]);
			return (ERR_DUP);
		}
		close(saved[1]);
		saved[1] = -1;
	}
	return (SUCCESS);
}
