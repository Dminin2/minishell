/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:42:22 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/04 13:33:00 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child(t_pipeline *pipeline, pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	close_pipes(pipeline->pipes, pipeline->n - 1);
	close_heredoc(pipeline->cmd_lst);
	while (i < pipeline->n)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	free(pids);
	free_pipeline(pipeline);
}

void	wait_child_fork_pos(t_pipeline *pipeline, pid_t *pids, int pos)
{
	int	i;
	int	status;

	i = 0;
	close_pipes(pipeline->pipes, pipeline->n - 1);
	close_heredoc(pipeline->cmd_lst);
	while (i < pos)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
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
			run_in_child(pipeline, i, minishell->env_lst);
		}
		i++;
	}
	return (0);
}

void	child_process(t_minishell *minishell, t_pipeline *pipeline)
{
	t_status	status;
	pid_t		*pids;
	int			fork_pos;

	status = create_pipes(pipeline);
	if (status != SUCCESS)
	{
		assert_error_parent(pipeline, "malloc", ERR_SYSTEM);
		return ;
	}
	status = pipe_pipes(pipeline->pipes, pipeline->n - 1);
	if (status != SUCCESS)
	{
		assert_error_parent(pipeline, "pipe", ERR_SYSTEM);
		return ;
	}
	pids = ft_calloc(pipeline->n, sizeof(pid_t));
	if (!pids)
	{
		assert_error_parent(pipeline, "malloc", ERR_SYSTEM);
		return ;
	}
	fork_pos = fork_all_children(minishell, pipeline, pids);
	if (fork_pos)
	{
		wait_child_fork_pos(pipeline, pids, fork_pos);
		assert_error_parent(pipeline, "fork", ERR_SYSTEM);
		return ;
	}
	wait_child(pipeline, pids);
}
