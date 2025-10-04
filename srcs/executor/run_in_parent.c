/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_in_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:35:35 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/04 13:27:15 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir_err_in_parent(t_pipeline *pipeline, t_redir_err err,
		int *saved)
{
	t_status	status;

	status = restore_stdio_fd(saved);
	if (status != SUCCESS)
		assert_error_parent(pipeline, "dup", status);
	if (err.status == ERR_FILE)
		assert_error_parent(pipeline, err.redir_err->value, ERR_FILE);
	else if (err.status == ERR_DUP)
		assert_error_parent(pipeline, "dup", ERR_DUP);
}

void	run_builtin_in_parent(t_pipeline *pipeline,
		t_command_type type)
{
	int			saved[2];
	t_redir_err	err;
	t_cmd		*cmd;
	t_status	status;

	saved[0] = -1;
	saved[1] = -1;
	err.redir_err = NULL;
	err.status = SUCCESS;
	cmd = pipeline->cmd_lst->content;
	status = save_stdio_fd(cmd->redir_lst, saved);
	if (status != SUCCESS)
	{
		assert_error_parent(pipeline, "dup", status);
		return ;
	}
	redirect(cmd->redir_lst, &err);
	if (err.status != SUCCESS)
	{
		handle_redir_err_in_parent(pipeline, err, saved);
		return ;
	}
	execute_builtin(cmd, type);
	status = restore_stdio_fd(saved);
	if (status != SUCCESS)
	{
		assert_error_parent(pipeline, "dup", status);
		return ;
	}
	free_pipeline(pipeline);
}
