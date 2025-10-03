/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 01:17:52 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/03 22:11:47 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_wrapper(void *cmd)
{
	free_cmd((t_cmd *)cmd);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->args)
			free_args(cmd->args);
		if (cmd->path)
			free(cmd->path);
		if (cmd->redir_lst)
			ft_lstclear(&(cmd->redir_lst), &free_redir_wrapper);
		free(cmd);
	}
}

void	free_pipeline(t_pipeline *pipeline)
{
	if (pipeline)
	{
		if (pipeline->cmd_lst)
			ft_lstclear(&(pipeline->cmd_lst), &free_cmd_wrapper);
		if (pipeline->pipes)
		{
			close_pipes(pipeline->pipes, pipeline->n - 1);
			free_pipes(pipeline->pipes, pipeline->n - 1);
		}
		free(pipeline);
	}
}
