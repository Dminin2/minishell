/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:28:07 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/04 21:51:14 by aomatsud         ###   ########.fr       */
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
		err->status = ERR_DUP;
		err->redir_err = NULL;
		return ;
	}
	close(redir->fd_hd);
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
}

void	redirect(t_list *redir_lst, t_redir_err *err)
{
	t_redir	*redir;

	while (redir_lst)
	{
		redir = redir_lst->content;
		if (redir->type == R_IN)
			redir_in(redir, err);
		else if (redir->type == R_OUT)
			redir_out(redir, err);
		else if (redir->type == R_HEREDOC)
			redir_heredoc(redir, err);
		else
			redir_append(redir, err);
		if (err->status != SUCCESS)
			return ;
		redir_lst = redir_lst->next;
	}
}
