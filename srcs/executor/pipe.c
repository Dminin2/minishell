/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:32:57 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/09 19:44:24 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	create_pipes(t_pipeline *pipeline)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = ft_calloc(pipeline->n - 1, sizeof(int *));
	if (!pipes)
		return (ERR_MALLOC);
	while (i < pipeline->n - 1)
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		if (!pipes[i])
		{
			close_pipes(pipes, i);
			free_pipes(pipes, i);
			return (ERR_MALLOC);
		}
		i++;
	}
	pipeline->pipes = pipes;
	return (SUCCESS);
}

t_status	pipe_pipes(int **pipes, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pipe(pipes[i]) == -1)
			return (ERR_PIPE);
		i++;
	}
	return (SUCCESS);
}

t_status	pipe_duplicate(t_pipeline *pipeline, int pos)
{
	if (pos != 0)
	{
		if (dup2(pipeline->pipes[pos - 1][0], STDIN_FILENO) == -1)
			return (ERR_DUP);
	}
	if (pos != pipeline->n - 1)
	{
		if (dup2(pipeline->pipes[pos][1], STDOUT_FILENO) == -1)
			return (ERR_DUP);
	}
	return (SUCCESS);
}
