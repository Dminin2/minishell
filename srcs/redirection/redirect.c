/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:28:07 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/08 12:47:35 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_and_set_error(t_redir_err *err, t_status status,
		char *tmp_fname, int should_unlink)
{
	err->redir_err = NULL;
	err->status = status;
	if (tmp_fname)
	{
		if (should_unlink)
			unlink(tmp_fname);
		free(tmp_fname);
	}
}

void	expand_heredoc_and_replace_fd(t_minishell *minishell, t_redir *redir,
		t_redir_err *err)
{
	t_status	status;
	int			tmp_fd;
	char		*tmp_fname;

	status = create_hd_filename(&tmp_fname);
	if (status != SUCCESS)
		return (cleanup_and_set_error(err, status, NULL, 0));
	tmp_fd = open(tmp_fname, O_CREAT | O_EXCL | O_WRONLY | O_CLOEXEC, 0600);
	if (tmp_fd < 0)
		return (cleanup_and_set_error(err, ERR_HD_FILE, tmp_fname, 0));
	status = expand_heredoc(minishell, redir->fd_hd, tmp_fd);
	close(redir->fd_hd);
	redir->fd_hd = -1;
	close(tmp_fd);
	if (status != SUCCESS)
		return (cleanup_and_set_error(err, status, tmp_fname, 1));
	redir->fd_hd = open(tmp_fname, O_RDONLY | O_CLOEXEC);
	unlink(tmp_fname);
	free(tmp_fname);
	if (redir->fd_hd < 0)
		return (cleanup_and_set_error(err, ERR_HD_FILE, NULL, 0));
}

void	redir_heredoc(t_minishell *minishell, t_redir *redir, t_redir_err *err)
{
	if (!redir->delimiter_is_quoted)
	{
		expand_heredoc_and_replace_fd(minishell, redir, err);
		if (err->status != SUCCESS)
			return ;
	}
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

static void	expand_redir_value(t_minishell *minishell, t_redir *redir,
		t_redir_err *err)
{
	char	*new_value;
	int		is_quoted;

	is_quoted = 0;
	new_value = expand_string(minishell, redir->value, &is_quoted);
	if (!new_value)
	{
		err->status = ERR_MALLOC;
		return ;
	}
	if (!is_quoted && new_value[0] == '\0')
	{
		free(new_value);
		err->redir_err = redir;
		err->status = ERR_AMB_REDIR;
		return ;
	}
	free(redir->value);
	redir->value = new_value;
	err->status = SUCCESS;
}

void	redirect(t_minishell *minishell, t_list *redir_lst, t_redir_err *err)
{
	t_redir	*redir;

	while (redir_lst)
	{
		redir = redir_lst->content;
		if (redir->type != R_HEREDOC)
		{
			expand_redir_value(minishell, redir, err);
			if (err->status != SUCCESS)
				break ;
		}
		if (redir->type == R_IN)
			redir_in(redir, err);
		else if (redir->type == R_OUT)
			redir_out(redir, err);
		else if (redir->type == R_HEREDOC)
			redir_heredoc(minishell, redir, err);
		else
			redir_append(redir, err);
		if (err->status != SUCCESS)
			break ;
		redir_lst = redir_lst->next;
	}
}
