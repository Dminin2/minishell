/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_in_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:35:35 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/07 00:12:22 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir_err_in_parent(t_minishell *minishell, t_pipeline *pipeline,
		t_redir_err err, int *saved)
{
	t_status	status;

	status = restore_stdio_fd(saved);
	if (status != SUCCESS)
		return (error_pipeline(minishell, pipeline, "dup", status));
	if (err.status == ERR_FILE)
		error_pipeline(minishell, pipeline, err.redir_err->value, ERR_FILE);
	else if (err.status == ERR_DUP)
		error_pipeline(minishell, pipeline, "dup", ERR_DUP);
	else if (err.status == ERR_AMB_REDIR)
		error_pipeline(minishell, pipeline, err.redir_err->value,
			ERR_AMB_REDIR);
	else if (err.status == ERR_MALLOC)
		error_pipeline(minishell, pipeline, "malloc", ERR_MALLOC);
	else if (err.status == ERR_HD_FILE)
		error_pipeline(minishell, pipeline, HD_FILE_ERR, ERR_HD_FILE);
}

t_status	save_fd_and_redirect(t_minishell *minishell, t_pipeline *pipeline,
		t_cmd *cmd, int *saved)
{
	t_status	status;
	t_redir_err	err;

	saved[0] = -1;
	saved[1] = -1;
	err.redir_err = NULL;
	err.status = SUCCESS;
	status = save_stdio_fd(cmd->redir_lst, saved);
	if (status != SUCCESS)
	{
		error_pipeline(minishell, pipeline, "dup", status);
		return (ERR_DUP);
	}
	redirect(minishell, cmd->redir_lst, &err);
	if (err.status != SUCCESS)
	{
		handle_redir_err_in_parent(minishell, pipeline, err, saved);
		return (err.status);
	}
	return (SUCCESS);
}

void	run_builtin_in_parent(t_minishell *minishell, t_pipeline *pipeline,
		t_command_type type)
{
	int			saved[2];
	t_cmd		*cmd;
	t_status	status;

	cmd = pipeline->cmd_lst->content;
	status = save_fd_and_redirect(minishell, pipeline, cmd, saved);
	if (status != SUCCESS)
		return ;
	if (type == NO_CMD)
		minishell->last_status = 0;
	else
		execute_builtin(minishell, cmd, type, pipeline->n);
	status = restore_stdio_fd(saved);
	if (status != SUCCESS)
		return (error_pipeline(minishell, pipeline, "dup", status));
	free_pipeline(pipeline);
}
