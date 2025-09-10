/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 01:08:34 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/09 20:36:02 by aomatsud         ###   ########.fr       */
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
}

void	execute(t_pipeline *pipeline, int pos, char **envp)
{
	t_status	status;
	t_redir_err	err;
	t_cmd		*cmd;

	cmd = get_cmd_from_lst(pipeline->cmd_lst, pos);
	status = pipe_duplicate(pipeline, pos);
	close_pipes(pipeline->pipes, pipeline->n - 1);
	if (status != SUCCESS)
		exit_error(pipeline, "dup", status, EXIT_FAILURE);
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
