/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 01:08:34 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/04 20:24:10 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir_err(t_pipeline *pipeline, t_redir_err err)
{
	if (err.status == ERR_FILE)
		exit_error(pipeline, err.redir_err->value, ERR_FILE, EXIT_FAILURE);
	else if (err.status == ERR_DUP)
		exit_error(pipeline, "dup", ERR_SYSTEM, EXIT_FAILURE);
}

void	execute(t_pipeline *pipeline, char **envp)
{
	t_status	status;
	t_redir_err	err;
	t_cmd		*cmd;

	cmd = pipeline->cmd_lst->content;
	err.status = SUCCESS;
	err.redir_err = NULL;
	redirect(cmd->redir_lst, &err);
	if (err.status != SUCCESS)
		handle_redir_err(pipeline, err);
	status = resolve_command_path(cmd, envp);
	if (status != SUCCESS)
	{
		if (status == ERR_SYSTEM)
			exit_error(pipeline, "malloc", status, EXIT_FAILURE);
		else
			exit_error(pipeline, cmd->args[0], status, 127);
	}
	if (access(cmd->path, X_OK) != 0)
		exit_error(pipeline, cmd->path, ERR_SYSTEM, 127);
	else if (execve(cmd->path, cmd->args, envp) == -1)
		exit_error(pipeline, cmd->path, ERR_SYSTEM, 127);
}
