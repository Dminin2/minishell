/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:42:22 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/07 01:00:37 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	finalize_wait(t_minishell *minishell, int err, int status)
{
	if (g_sig == SIGINT)
	{
		ft_dprintf_buf(STDERR_FILENO, "\n");
		g_sig = 0;
	}
	if (err)
		minishell->last_status = 1;
	else if (WIFEXITED(status))
		minishell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_dprintf_buf(STDERR_FILENO, "Quit\n");
		minishell->last_status = 128 + WTERMSIG(status);
	}
	else
		minishell->last_status = 1;
	if (isatty(STDIN_FILENO))
		set_signal_interactive();
}

static int	wait_all_pids(int pids_count, int *status, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < pids_count)
	{
		if (waitpid(pids[i], status, 0) == -1)
		{
			if (errno == EINTR)
				continue ;
			print_error_msg("waitpid", ERR_WAITPID);
			if (i == pids_count - 1)
				return (1);
		}
		else if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
			g_sig = SIGINT;
		i++;
	}
	return (0);
}

void	wait_child(t_minishell *minishell, t_pipeline *pipeline, pid_t *pids,
		int pids_count)
{
	int	status;
	int	err;

	close_pipes(pipeline->pipes, pipeline->n - 1);
	close_heredoc(pipeline->cmd_lst);
	if (pids_count <= 0)
	{
		free(pids);
		return ;
	}
	if (isatty(STDIN_FILENO))
		set_signal_wait_child();
	err = wait_all_pids(pids_count, &status, pids);
	finalize_wait(minishell, err, status);
	free(pids);
}

int	fork_all_children(t_minishell *minishell, t_pipeline *pipeline, pid_t *pids,
		char *last_arg)
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
			free(last_arg);
			free(pids);
			set_signal_default();
			run_in_child(minishell, pipeline, i);
		}
		i++;
	}
	return (i);
}

void	child_process(t_minishell *minishell, t_pipeline *pipeline,
		char *last_arg)
{
	t_status	status;
	pid_t		*pids;
	int			fork_pos;

	status = create_pipes(pipeline);
	if (status != SUCCESS)
		return (error_pipeline(minishell, pipeline, "malloc", ERR_MALLOC));
	status = pipe_pipes(pipeline->pipes, pipeline->n - 1);
	if (status != SUCCESS)
		return (error_pipeline(minishell, pipeline, "pipe", ERR_PIPE));
	pids = ft_calloc(pipeline->n, sizeof(pid_t));
	if (!pids)
		return (error_pipeline(minishell, pipeline, "malloc", ERR_MALLOC));
	fork_pos = fork_all_children(minishell, pipeline, pids, last_arg);
	if (fork_pos != pipeline->n)
	{
		wait_child(minishell, pipeline, pids, fork_pos);
		return (error_pipeline(minishell, pipeline, "fork", ERR_FORK));
	}
	wait_child(minishell, pipeline, pids, pipeline->n);
	free_pipeline(pipeline);
}
