/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 01:08:34 by aomatsud          #+#    #+#             */
/*   Updated: 2025/08/19 16:38:23 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_cmd *cmd, char **envp)
{
	t_status	status;

	status = resolve_command_path(cmd, envp);
	if (status != SUCCESS)
	{
		if (status == ERR_SYSTEM)
			exit_error(cmd, "malloc", status, EXIT_FAILURE);
		else
			exit_error(cmd, cmd->args[0], status, 127);
	}
	if (access(cmd->path, X_OK) != 0)
		exit_error(cmd, cmd->path, ERR_SYSTEM, 127);
	else if (execve(cmd->path, cmd->args, envp) == -1)
		exit_error(cmd, cmd->path, ERR_SYSTEM, 127);
}
