/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:28:07 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/13 18:06:32 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_in(t_redir *redir, t_redir_err *err)
{
	int	fd;

	fd = open(redir->value, O_RDONLY);
	if (fd < 0)
	{
		err->status = ERR_FILE;
		err->redir_err = redir;
		return ;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		err->status = ERR_DUP;
		err->redir_err = NULL;
		return ;
	}
	close(fd);
}

void	redir_out(t_redir *redir, t_redir_err *err)
{
	int	fd;

	fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		err->status = ERR_FILE;
		err->redir_err = redir;
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		err->status = ERR_DUP;
		err->redir_err = NULL;
		return ;
	}
	close(fd);
}

void	redir_heredoc(t_redir *redir, t_redir_err *err)
{
	if (dup2(redir->fd_hd, STDIN_FILENO) < 0)
	{
		close(redir->fd_hd);
		redir->fd_hd = -1;
		err->status = ERR_DUP;
		err->redir_err = NULL;
		return ;
	}
	close(redir->fd_hd);
	redir->fd_hd = -1;
}

void	redir_append(t_redir *redir, t_redir_err *err)
{
	int	fd;

	fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		err->status = ERR_FILE;
		err->redir_err = redir;
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		err->status = ERR_DUP;
		err->redir_err = NULL;
		return ;
	}
	close(fd);
}

void	redirect(t_minishell *minishell, t_list *redir_lst, t_redir_err *err)
{
	t_redir	*redir;
	char	*new_value;
	int		is_quoted;

#ifdef DEBUG
	t_list	*head;
	head = redir_lst;
#endif
	while (redir_lst)
	{
		is_quoted = 0;
		redir = redir_lst->content;
		if (redir->type != R_HEREDOC)
		{
			new_value = expand_filename(minishell, redir->value, &is_quoted);
			if (!new_value)
			{
				err->status = ERR_MALLOC;
				break ;
			}
			if (!is_quoted && new_value[0] == '\0')
			{
				free(new_value);
				err->redir_err = redir;
				err->status = ERR_AMB_REDIR;
				break ;
			}
			free(redir->value);
			redir->value = new_value;
		}
		if (redir->type == R_IN)
			redir_in(redir, err);
		else if (redir->type == R_OUT)
			redir_out(redir, err);
		else if (redir->type == R_HEREDOC)
			redir_heredoc(redir, err);
		else
			redir_append(redir, err);
		if (err->status != SUCCESS)
			break ;
		redir_lst = redir_lst->next;
	}
#ifdef DEBUG
	dprintf(g_fd, "=== after expand ===\n");
	print_redir_lst(head, g_fd);
#endif
}
