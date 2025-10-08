/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_in_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 01:08:34 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/07 23:48:59 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_cmd_from_lst(t_list *head, int target)
{
	int		i;
	t_list	*lst;

	i = 0;
	lst = head;
	while (lst && i < target)
	{
		lst = lst->next;
		i++;
	}
	if (!lst)
		return (NULL);
	else
		return (lst->content);
}

void	handle_redir_err(t_pipeline *pipeline, t_redir_err err)
{
	if (err.status == ERR_FILE)
		exit_error(pipeline, err.redir_err->value, ERR_FILE, EXIT_FAILURE);
	else if (err.status == ERR_DUP)
		exit_error(pipeline, "dup", ERR_SYSTEM, EXIT_FAILURE);
	else if (err.status == ERR_AMB_REDIR)
		exit_error(pipeline, err.redir_err->value, ERR_AMB_REDIR, EXIT_FAILURE);
}

void	handle_execve_error(t_pipeline *pipeline, t_cmd *cmd)
{
	if (errno == EISDIR)
		exit_error(pipeline, cmd->args[0], ERR_ISDIR, 126);
	else
		exit_error(pipeline, cmd->args[0], ERR_ERRNO, 126);
}

void	run_in_child(t_minishell *minishell, t_pipeline *pipeline, int pos)
{
	t_status		status;
	t_redir_err		err;
	t_cmd			*cmd;
	struct stat		st_buf;
	t_command_type	type;
	char			**envp;

	cmd = get_cmd_from_lst(pipeline->cmd_lst, pos);
	status = pipe_duplicate(pipeline, pos);
	close_pipes(pipeline->pipes, pipeline->n - 1);
	if (status != SUCCESS)
		exit_error(pipeline, "dup", status, EXIT_FAILURE);
	err.status = SUCCESS;
	err.redir_err = NULL;
	redirect(minishell, cmd->redir_lst, &err);
	if (err.status != SUCCESS)
		handle_redir_err(pipeline, err);
	type = scan_command_type(cmd);
	if (type != EXTERNAL && type != NO_CMD)
	{
		execute_builtin(minishell, cmd, type);
		free_pipeline(pipeline);
		exit(minishell->last_status);
	}
	else if (type == NO_CMD)
		exit_success(pipeline);
	status = resolve_command_path(cmd, minishell->env_lst);
	if (status != SUCCESS)
	{
		if (status == ERR_SYSTEM)
			exit_error(pipeline, "malloc", status, EXIT_FAILURE);
		else
			exit_error(pipeline, cmd->args[0], status, 127);
	}
	if (stat(cmd->path, &st_buf) == -1)
		exit_error(pipeline, cmd->path, ERR_ERRNO, 127);
	if (S_ISDIR(st_buf.st_mode))
		exit_error(pipeline, cmd->path, ERR_ISDIR, 126);
	if (access(cmd->path, X_OK) == -1)
		exit_error(pipeline, cmd->path, ERR_SYSTEM, 126);
	envp = pack_env(minishell->env_lst);
	if (!envp)
		exit_error(pipeline, "malloc", ERR_MALLOC, EXIT_FAILURE);
	if (execve(cmd->path, cmd->args, envp) == -1)
	{
		free_args(envp);
		handle_execve_error(pipeline, cmd);
	}
}
