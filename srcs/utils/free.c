/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:17:00 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/14 12:38:24 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
}

void	free_token_wrapper(void *tok)
{
	free_token((t_token *)tok);
}

void	free_token(t_token *tok)
{
	if (tok)
	{
		if (tok->value)
			free(tok->value);
		free(tok);
	}
}

void	free_redir_wrapper(void *redir)
{
	free_redir((t_redir *)redir);
}

void	free_redir(t_redir *redir)
{
	if (redir)
	{
		if (redir->value)
			free(redir->value);
		free(redir);
	}
}

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

void	free_str_wrapper(void *str)
{
	free_str((char *)str);
}

void	free_str(char *str)
{
	free(str);
}

void	free_cmd_ir_wrapper(void *cmd_ir)
{
	free_cmd_ir((t_cmd_ir *)cmd_ir);
}

void	free_cmd_ir(t_cmd_ir *cmd_ir)
{
	if (cmd_ir)
	{
		if (cmd_ir->args_lst)
			ft_lstclear(&(cmd_ir->args_lst), &free_str_wrapper);
		if (cmd_ir->redir_lst)
			ft_lstclear(&(cmd_ir->redir_lst), &free_redir_wrapper);
		free(cmd_ir);
	}
}

void	free_pipes(int **pipes, int n)
{
	int	i;

	i = 0;
	if (pipes)
	{
		while (i < n)
		{
			free(pipes[i]);
			i++;
		}
		free(pipes);
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

void	free_pipeline_ir(t_pipeline_ir *pipeline_ir)
{
	if (pipeline_ir)
	{
		if (pipeline_ir->cmd_ir_lst)
			ft_lstclear(&(pipeline_ir->cmd_ir_lst), &free_cmd_ir_wrapper);
		free(pipeline_ir);
	}
}
