/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:38:36 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/15 13:22:57 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	set_underscore_for_invocation(t_minishell *minishell,
		t_cmd *cmd, t_command_type type)
{
	t_status	status;
	char		*value;
	t_cmd		underscore_cmd;

	value = cmd->args[0];
	if (type == EXTERNAL)
	{
		underscore_cmd.args = cmd->args;
		status = resolve_command_path(&underscore_cmd, minishell->env_lst);
		if (status == ERR_SYSTEM)
			return (ERR_SYSTEM);
		if (underscore_cmd.path)
			value = underscore_cmd.path;
	}
	status = add_env(&(minishell->env_lst), "_", value);
	if (type == EXTERNAL && value != cmd->args[0])
		free(value);
	return (status);
}

static t_status	set_underscore_to_last_arg(t_minishell *minishell, t_cmd *cmd,
		t_command_type type)
{
	int	i;

	if (type == NO_CMD)
		return (add_env(&(minishell->env_lst), "_", ""));
	i = 0;
	while (cmd->args[i + 1])
		i++;
	return (add_env(&(minishell->env_lst), "_", cmd->args[i]));
}

void	execute(t_minishell *minishell, t_pipeline *pipeline)
{
	t_command_type	type;
	t_cmd			*cmd;
	t_status		status;

	if (pipeline->n != 1)
	{
		child_process(minishell, pipeline);
		return ;
	}
	cmd = pipeline->cmd_lst->content;
	type = scan_command_type(cmd);
	status = set_underscore_for_invocation(minishell, cmd, type);
	if (status == ERR_SYSTEM)
	{
		minishell->last_status = assert_error_parent(pipeline, "malloc",
				ERR_MALLOC);
		return ;
	}
	if (type == EXTERNAL)
		child_process(minishell, pipeline);
	else
		run_builtin_in_parent(minishell, pipeline, type);
	status = set_underscore_to_last_arg(minishell, cmd, type);
	if (status == ERR_SYSTEM)
		minishell->last_status = assert_error_parent(pipeline, "malloc",
				ERR_MALLOC);
}
