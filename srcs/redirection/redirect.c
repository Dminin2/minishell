/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:28:07 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/31 14:44:01 by aomatsud         ###   ########.fr       */
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

void	expand_heredoc_and_replace_fd(t_minishell *minishell, t_redir *redir,
		t_redir_err *err)
{
	t_status	status;
	int			tmp_fd;
	char		*tmp_fname;

	status = create_hd_filename(&tmp_fname);
	if (status != SUCCESS)
	{
		err->redir_err = NULL;
		err->status = status;
		return ;
	}
	tmp_fd = open(tmp_fname, O_CREAT | O_EXCL | O_WRONLY, 0600);
	if (tmp_fd < 0)
	{
		err->redir_err = NULL;
		err->status = ERR_HD_FILE;
		free(tmp_fname);
		return ;
	}
	status = expand_heredoc(minishell, redir->fd_hd, tmp_fd);
	close(redir->fd_hd);
	close(tmp_fd);
	if (status != SUCCESS)
	{
		unlink(tmp_fname);
		free(tmp_fname);
		err->redir_err = NULL;
		err->status = status;
		return ;
	}
	redir->fd_hd = open(tmp_fname, O_RDONLY);
	unlink(tmp_fname);
	free(tmp_fname);
	if (redir->fd_hd < 0)
	{
		err->redir_err = NULL;
		err->status = ERR_HD_FILE;
		return ;
	}
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
			redir_heredoc(minishell, redir, err);
		else
			redir_append(redir, err);
		if (err->status != SUCCESS)
			break ;
		redir_lst = redir_lst->next;
	}
#ifdef DEBUG
	ft_dprintf(g_fd, "=== after expand ===\n");
	print_redir_lst(head, g_fd);
#endif
}
