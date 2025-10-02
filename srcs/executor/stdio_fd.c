/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:13:47 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/03 00:14:26 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	save_stdio_fd(t_list *redir_lst, int *saved)
{
	t_redir	*redir;

	while (redir_lst)
	{
		redir = redir_lst->content;
		if (redir->type == R_IN || redir->type == R_HEREDOC)
		{
			if (saved[0] == -1)
			{
				saved[0] = dup(STDIN_FILENO);
				if (saved[0] == -1)
					return (ERR_DUP);
			}
		}
		else
		{
			if (saved[1] == -1)
			{
				saved[1] = dup(STDOUT_FILENO);
				if (saved[1] == -1)
					return (ERR_DUP);
			}
		}
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
