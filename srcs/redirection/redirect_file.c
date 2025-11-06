/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:19:26 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/05 18:42:55 by hmaruyam         ###   ########.fr       */
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
