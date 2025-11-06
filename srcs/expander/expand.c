/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 22:14:28 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/06 13:11:19 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	expand_args_lst(t_minishell *minishell, t_list *args_lst)
{
	char	*old_value;
	char	*new_value;
	int		is_quoted;

	while (args_lst)
	{
		is_quoted = 0;
		old_value = args_lst->content;
		new_value = expand_string(minishell, old_value, &is_quoted);
		if (!new_value)
			return (ERR_MALLOC);
		if (!is_quoted && new_value[0] == '\0')
		{
			free(new_value);
			new_value = NULL;
		}
		free(old_value);
		args_lst->content = new_value;
		args_lst = args_lst->next;
	}
	return (SUCCESS);
}

static t_status	expand_and_convert_args(t_minishell *minishell,
		t_list *args_lst, t_cmd *cmd)
{
	t_status	status;

	status = expand_args_lst(minishell, args_lst);
	if (status != SUCCESS)
		return (status);
	status = convert_list_to_array(args_lst, cmd);
	return (status);
}

static t_list	*handle_cmd_error(t_minishell *minishell, t_list **head,
		t_cmd *cmd)
{
	if (cmd)
		free_cmd(cmd);
	minishell->last_status = error_lst(*head, "malloc", ERR_MALLOC,
			free_cmd_wrapper);
	minishell->should_exit = 1;
	return (NULL);
}

static t_list	*get_cmd_lst(t_minishell *minishell, t_list *cmd_ir_lst)
{
	t_cmd		*cmd;
	t_list		*head;
	t_status	status;
	t_cmd_ir	*cmd_ir;

	head = NULL;
	status = SUCCESS;
	while (cmd_ir_lst)
	{
		cmd_ir = cmd_ir_lst->content;
		cmd = ft_calloc(1, sizeof(t_cmd));
		if (!cmd)
			return (handle_cmd_error(minishell, &head, cmd));
		if (cmd_ir->args_lst)
			status = expand_and_convert_args(minishell, cmd_ir->args_lst, cmd);
		if (status != SUCCESS)
			return (handle_cmd_error(minishell, &head, cmd));
		cmd->redir_lst = cmd_ir->redir_lst;
		cmd_ir->redir_lst = NULL;
		status = add_newlst(&head, cmd);
		if (status != SUCCESS)
			return (handle_cmd_error(minishell, &head, cmd));
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
		minishell->last_status = error_lst(NULL, "malloc", ERR_MALLOC, NULL);
		minishell->should_exit = 1;
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
