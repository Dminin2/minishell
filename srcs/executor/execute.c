/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 01:08:34 by aomatsud          #+#    #+#             */
/*   Updated: 2025/08/18 20:58:13 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_cmd *cmd, char **envp)
{
	if (access(cmd->path, X_OK) != 0)
		exit_error(cmd, cmd->path, ERR_SYSTEM, 127);
	else if (execve(cmd->path, cmd->args, envp) == -1)
		exit_error(cmd, cmd->path, ERR_SYSTEM, 127);
}
