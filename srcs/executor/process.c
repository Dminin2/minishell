/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:42:22 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/04 20:36:09 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child(t_pipeline *pipeline, pid_t pid)
{
	int	status;

	close_heredoc(pipeline->cmd_lst);
	free_pipeline(pipeline);
	waitpid(pid, &status, 0);
}

void	child_process(t_pipeline *pipeline, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit_error(pipeline, "fork", ERR_SYSTEM, EXIT_FAILURE);
	else if (pid == 0)
		execute(pipeline, envp);
	else
		wait_child(pipeline, pid);
}
