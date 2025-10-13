/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:42:22 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/13 15:22:17 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child(t_minishell *minishell, t_pipeline *pipeline, pid_t *pids,
		int pids_count)
{
	int	i;
	int	status;
	int	err;

	i = 0;
	err = 0;
	close_pipes(pipeline->pipes, pipeline->n - 1);
	close_heredoc(pipeline->cmd_lst);
	if (pids_count <= 0)
	{
		free(pids);
		return ;
	}
	while (i < pids_count)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			if (errno == EINTR)
				continue ;
			print_error_msg("waitpid", ERR_WAITPID);
			if (i == pids_count - 1)
				err = 1;
		}
		i++;
	}
	if (err)
		minishell->last_status = 1;
	else if (WIFEXITED(status))
		minishell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		minishell->last_status = 128 + WTERMSIG(status);
	else
		minishell->last_status = 1;
	free(pids);
}

int	fork_all_children(t_minishell *minishell, t_pipeline *pipeline, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < pipeline->n)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (i);
		if (pids[i] == 0)
		{
			free(pids);
			run_in_child(minishell, pipeline, i);
		}
		i++;
	}
	return (i);
}

void	child_process(t_minishell *minishell, t_pipeline *pipeline)
{
	t_status	status;
	pid_t		*pids;
	int			fork_pos;

	status = create_pipes(pipeline);
	if (status != SUCCESS)
	{
		minishell->last_status = assert_error_parent(pipeline, "malloc", ERR_SYSTEM);
		return ;
	}
	status = pipe_pipes(pipeline->pipes, pipeline->n - 1);
	if (status != SUCCESS)
	{
		minishell->last_status = assert_error_parent(pipeline, "pipe", ERR_SYSTEM);
		return ;
	}
	pids = ft_calloc(pipeline->n, sizeof(pid_t));
	if (!pids)
	{
		minishell->last_status = assert_error_parent(pipeline, "malloc", ERR_SYSTEM);
		return ;
	}
	fork_pos = fork_all_children(minishell, pipeline, pids);
	if (fork_pos != pipeline->n)
	{
		wait_child(minishell, pipeline, pids, fork_pos);
		minishell->last_status = 1;
		minishell->last_status = assert_error_parent(pipeline, "fork", ERR_SYSTEM);
		return ;
	}
	wait_child(minishell, pipeline, pids, pipeline->n);
	free_pipeline(pipeline);
}
