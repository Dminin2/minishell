/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_in_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 01:08:34 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/07 01:08:10 by hmaruyam         ###   ########.fr       */
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

static void	execute_external_command(t_minishell *minishell,
		t_pipeline *pipeline, t_cmd *cmd)
{
	t_status	status;
	char		**envp;

	status = resolve_command_path(cmd, minishell->env_lst);
	if (status != SUCCESS)
	{
		if (status == ERR_MALLOC)
			exit_error(minishell, pipeline, "malloc", status);
		else
			exit_error(minishell, pipeline, cmd->args[0], status);
	}
	envp = pack_env(minishell->env_lst);
	if (!envp)
		exit_error(minishell, pipeline, "malloc", ERR_MALLOC);
	if (execve(cmd->path, cmd->args, envp) == -1)
	{
		free_args(envp);
		handle_execve_error(minishell, pipeline, cmd);
	}
}

static void	execute_builtin_in_child(t_minishell *minishell, t_cmd *cmd,
		t_command_type type, t_pipeline *pipeline)
{
	execute_builtin(minishell, cmd, type, pipeline->n);
	free_pipeline(pipeline);
	ft_lstclear(&(minishell->env_lst), free_env_wrapper);
	free(minishell->cwd);
	exit(minishell->last_status);
}

static void	setup_child_io(t_minishell *minishell, t_pipeline *pipeline,
		int pos, t_cmd *cmd)
{
	t_status	status;
	t_redir_err	err;

	status = pipe_duplicate(pipeline, pos);
	close_pipes(pipeline->pipes, pipeline->n - 1);
	if (status != SUCCESS)
		exit_error(minishell, pipeline, "dup", status);
	err.status = SUCCESS;
	err.redir_err = NULL;
	redirect(minishell, cmd->redir_lst, &err);
	if (err.status != SUCCESS)
		handle_redir_error(minishell, pipeline, err);
}

void	run_in_child(t_minishell *minishell, t_pipeline *pipeline, int pos)
{
	t_status		status;
	t_cmd			*cmd;
	t_command_type	type;

	cmd = get_cmd_from_lst(pipeline->cmd_lst, pos);
	setup_child_io(minishell, pipeline, pos, cmd);
	type = scan_command_type(cmd);
	status = set_underscore_for_invocation(minishell, cmd, type);
	if (status != SUCCESS)
		exit_error(minishell, pipeline, "malloc", ERR_MALLOC);
	if (type != EXTERNAL && type != NO_CMD)
		execute_builtin_in_child(minishell, cmd, type, pipeline);
	else if (type == NO_CMD)
		exit_success(minishell, pipeline);
	else
		execute_external_command(minishell, pipeline, cmd);
}
