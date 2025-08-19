/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:42:22 by aomatsud          #+#    #+#             */
/*   Updated: 2025/08/18 09:35:37 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
}

void	child_process(t_cmd *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit_error(cmd, "fork", ERR_SYSTEM, EXIT_FAILURE);
	else if (pid == 0)
		execute(cmd, envp);
	else
		wait_child(pid);
}
