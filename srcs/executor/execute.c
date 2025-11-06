/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:38:36 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/07 00:43:06 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	set_underscore_for_invocation(t_minishell *minishell, t_cmd *cmd,
		t_command_type type)
{
	t_status	status;
	char		*value;
	t_cmd		underscore_cmd;

	if (type == NO_CMD)
		value = "";
	else
		value = cmd->args[0];
	if (type == EXTERNAL)
	{
		underscore_cmd.args = cmd->args;
		underscore_cmd.path = NULL;
		status = resolve_command_path(&underscore_cmd, minishell->env_lst);
		if (status == ERR_MALLOC)
			return (ERR_MALLOC);
		if (underscore_cmd.path)
			value = underscore_cmd.path;
	}
	status = process_env_key_value(&(minishell->env_lst), "_", value);
	if (type == EXTERNAL && value != cmd->args[0])
		free(value);
	return (status);
}

static char	*get_last_arg(t_cmd *cmd, t_command_type type)
{
	int		i;
	char	*last_arg;

	if (type == NO_CMD)
		last_arg = ft_strdup("");
	else
	{
		i = 0;
		while (cmd->args[i + 1])
			i++;
		last_arg = ft_strdup(cmd->args[i]);
	}
	return (last_arg);
}

static t_status	prepare_execution(t_minishell *minishell, t_command_type *type,
		t_cmd *cmd, char **last_arg)
{
	t_status	status;

	status = SUCCESS;
	*type = scan_command_type(cmd);
	*last_arg = get_last_arg(cmd, *type);
	if (!*last_arg)
		return (ERR_MALLOC);
	if (*type != NO_CMD)
		status = set_underscore_for_invocation(minishell, cmd, *type);
	return (status);
}

void	execute(t_minishell *minishell, t_pipeline *pipeline)
{
	t_command_type	type;
	t_cmd			*cmd;
	t_status		status;
	char			*last_arg;

	if (pipeline->n != 1)
		return (child_process(minishell, pipeline, NULL));
	cmd = pipeline->cmd_lst->content;
	status = prepare_execution(minishell, &type, cmd, &last_arg);
	if (status == ERR_MALLOC)
	{
		free(last_arg);
		return (error_parent(minishell, pipeline, "malloc", ERR_MALLOC));
	}
	if (type == EXTERNAL)
		child_process(minishell, pipeline, last_arg);
	else
		run_builtin_in_parent(minishell, pipeline, type);
	status = process_env_key_value(&(minishell->env_lst), "_", last_arg);
	free(last_arg);
	if (status == ERR_MALLOC)
		error_parent(minishell, NULL, "malloc", ERR_MALLOC);
}
