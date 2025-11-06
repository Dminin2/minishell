/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:13:14 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/07 00:57:44 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir_error(t_minishell *minishell, t_pipeline *pipeline,
		t_redir_err err)
{
	if (err.status == ERR_FILE)
		exit_error(minishell, pipeline, err.redir_err->value, ERR_FILE);
	else if (err.status == ERR_DUP)
		exit_error(minishell, pipeline, "dup", ERR_DUP);
	else if (err.status == ERR_AMB_REDIR)
		exit_error(minishell, pipeline, err.redir_err->value, ERR_AMB_REDIR);
	else if (err.status == ERR_HD_FILE)
		exit_error(minishell, pipeline, HD_FILE_ERR, ERR_HD_FILE);
	else if (err.status == ERR_MALLOC)
		exit_error(minishell, pipeline, "malloc", ERR_MALLOC);
}

void	handle_execve_error(t_minishell *minishell, t_pipeline *pipeline,
		t_cmd *cmd)
{
	struct stat	st_buf;
	int			saved_errno;

	saved_errno = errno;
	if (stat(cmd->path, &st_buf) == 0 && S_ISDIR(st_buf.st_mode))
		exit_error(minishell, pipeline, cmd->path, ERR_ISDIR);
	else if (saved_errno == EACCES)
		exit_error(minishell, pipeline, cmd->path, ERR_EACCES);
	else if (saved_errno == ENOENT)
		exit_error(minishell, pipeline, cmd->path, ERR_ENOENT);
	else if (saved_errno == ENOTDIR)
		exit_error(minishell, pipeline, cmd->path, ERR_ENOTDIR);
	else
		exit_error(minishell, pipeline, cmd->path, ERR_EXECVE_OTHER);
}
