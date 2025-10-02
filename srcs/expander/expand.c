/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:14:28 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/02 21:56:13 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	expand_and_convert_args(t_minishell *minishell, t_list *args_lst,
		t_cmd *cmd)
{
	t_status	status;

	status = expand_args_lst(minishell, args_lst);
	if (status != SUCCESS)
		return (status);
	status = get_args_from_lst(args_lst, cmd);
	return (status);
}

t_list	*get_cmd_lst(t_minishell *minishell, t_list *cmd_ir_lst)
{
	t_cmd		*cmd;
	t_list		*head;
	t_status	status;
	t_cmd_ir	*cmd_ir;

	head = NULL;
	while (cmd_ir_lst)
	{
		cmd_ir = cmd_ir_lst->content;
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
		{
			assert_error_expander(head, "malloc", ERR_SYSTEM);
			return (NULL);
		}
		if (cmd_ir->args_lst)
		{
			status = expand_and_convert_args(minishell, cmd_ir->args_lst, cmd);
			if (status != SUCCESS)
			{
				free(cmd);
				assert_error_expander(head, "malloc", ERR_SYSTEM);
				return (NULL);
			}
		}
		status = add_newlst(&head, cmd);
		if (status != SUCCESS)
		{
			free(cmd);
			assert_error_expander(head, "malloc", ERR_SYSTEM);
			return (NULL);
		}
		cmd->redir_lst = cmd_ir->redir_lst;
		cmd_ir_lst = cmd_ir_lst->next;
	}
	return (head);
}

t_pipeline	*expand(t_minishell *minishell, t_pipeline_ir *pipeline_ir)
{
	t_pipeline	*pipeline;

	pipeline = ft_calloc(1, sizeof(t_pipeline));
	if (!pipeline)
	{
		assert_error_expander(NULL, "malloc", ERR_SYSTEM);
		return (NULL);
	}
	pipeline->cmd_lst = get_cmd_lst(minishell, pipeline_ir->cmd_ir_lst);
	if (!pipeline->cmd_lst)
	{
		free(pipeline);
		return (NULL);
	}
	pipeline->n = pipeline_ir->n;
	return (pipeline);
}
