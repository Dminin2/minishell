/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:23:07 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/02 22:41:48 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	add_newlst(t_list **head, void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
		return (ERR_SYSTEM);
	ft_lstadd_back(head, new);
	return (SUCCESS);
}

t_status	skip_pipe(t_list **tok_lst)
{
	*tok_lst = (*tok_lst)->next;
	if (!*tok_lst)
		return (ERR_SYNTAX);
	else
		return (SUCCESS);
}

t_list	*get_cmd_ir_lst(t_list *tok_lst)
{
	t_cmd_ir	*cmd_ir;
	t_status	status;
	t_list		*head;

	head = NULL;
	while (tok_lst)
	{
		cmd_ir = ft_calloc(1, sizeof(t_cmd_ir));
		if (!cmd_ir)
		{
			assert_error_lst(head, "malloc", ERR_SYSTEM, free_cmd_ir_wrapper);
			return (NULL);
		}
		status = get_simple_command(&tok_lst, cmd_ir);
		if (status != SUCCESS)
		{
			free_cmd_ir(cmd_ir);
			handle_error(tok_lst, head, status);
			return (NULL);
		}
		status = add_newlst(&head, (void *)cmd_ir);
		if (status == ERR_SYSTEM)
		{
			free_cmd_ir(cmd_ir);
			assert_error_lst(head, "malloc", ERR_SYSTEM, free_cmd_ir_wrapper);
			return (NULL);
		}
		if (tok_lst)
		{
			status = skip_pipe(&tok_lst);
			if (status == ERR_SYNTAX)
			{
				assert_error_lst(head, "newline", ERR_SYNTAX,
					free_cmd_ir_wrapper);
				return (NULL);
			}
		}
	}
	return (head);
}

int	count_cmd_irs(t_list *cmd_ir_lst)
{
	int	n;

	n = 0;
	while (cmd_ir_lst)
	{
		n++;
		cmd_ir_lst = cmd_ir_lst->next;
	}
	return (n);
}

t_pipeline_ir	*parse(t_list *tok_lst)
{
	t_pipeline_ir	*pipeline_ir;

	pipeline_ir = ft_calloc(1, sizeof(t_pipeline_ir));
	if (!pipeline_ir)
	{
		assert_error_lst(NULL, "malloc", ERR_SYSTEM, NULL);
		return (NULL);
	}
	pipeline_ir->cmd_ir_lst = get_cmd_ir_lst(tok_lst);
	if (!pipeline_ir->cmd_ir_lst)
	{
		free(pipeline_ir);
		return (NULL);
	}
	pipeline_ir->n = count_cmd_irs(pipeline_ir->cmd_ir_lst);
	return (pipeline_ir);
}
