/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_in_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 01:08:34 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/15 23:16:48 by aomatsud         ###   ########.fr       */
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

void	handle_redir_err(t_minishell *minishell, t_pipeline *pipeline,
		t_redir_err err)
{
	if (err.status == ERR_FILE)
		exit_error(minishell, pipeline, err.redir_err->value, ERR_FILE);
	else if (err.status == ERR_DUP)
		exit_error(minishell, pipeline, "dup", ERR_DUP);
	else if (err.status == ERR_AMB_REDIR)
		exit_error(minishell, pipeline, err.redir_err->value, ERR_AMB_REDIR);
}

void	handle_execve_error(t_minishell *minishell, t_pipeline *pipeline,
		t_cmd *cmd)
{
	if (errno == EISDIR)
		exit_error(minishell, pipeline, cmd->args[0], ERR_ISDIR);
	else
		exit_error(minishell, pipeline, cmd->args[0], ERR_ERRNO);
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
		exit_error(minishell, pipeline, "dup", status);
	err.status = SUCCESS;
	err.redir_err = NULL;
	redirect(minishell, cmd->redir_lst, &err);
	if (err.status != SUCCESS)
		handle_redir_err(minishell, pipeline, err);
	type = scan_command_type(cmd);
	if (type != EXTERNAL && type != NO_CMD)
	{
		execute_builtin(minishell, cmd, type, pipeline->n);
		free_pipeline(pipeline);
		exit(minishell->last_status);
	}
	else if (type == NO_CMD)
		exit_success(minishell, pipeline);
	status = resolve_command_path(cmd, minishell->env_lst);
	if (status != SUCCESS)
	{
		if (status == ERR_MALLOC)
			exit_error(minishell, pipeline, "malloc", status);
		else
			exit_error(minishell, pipeline, cmd->args[0], status);
	}
	if (stat(cmd->path, &st_buf) == -1)
		exit_error(minishell, pipeline, cmd->path, ERR_ERRNO);
	if (S_ISDIR(st_buf.st_mode))
		exit_error(minishell, pipeline, cmd->path, ERR_ISDIR);
	if (access(cmd->path, X_OK) == -1)
		exit_error(minishell, pipeline, cmd->path, ERR_ERRNO);
	envp = pack_env(minishell->env_lst);
	if (!envp)
		exit_error(minishell, pipeline, "malloc", ERR_MALLOC);
	if (execve(cmd->path, cmd->args, envp) == -1)
	{
		free_args(envp);
		handle_execve_error(minishell, pipeline, cmd);
	}
}
