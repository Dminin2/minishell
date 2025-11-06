/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:23:07 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/06 16:22:51 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	skip_pipe(t_list **tok_lst)
{
	*tok_lst = (*tok_lst)->next;
	if (!*tok_lst)
		return (ERR_SYNTAX);
	else
		return (SUCCESS);
}

t_list	*get_cmd_ir_lst(t_minishell *minishell, t_list *tok_lst)
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
			error_cmd_ir_lst(minishell, head, "malloc", ERR_MALLOC);
			return (NULL);
		}
		status = get_simple_command(&tok_lst, cmd_ir);
		if (status != SUCCESS)
		{
			free_cmd_ir(cmd_ir);
			handle_error(minishell, tok_lst, head, status);
			return (NULL);
		}
		status = add_newlst(&head, (void *)cmd_ir);
		if (status == ERR_MALLOC)
		{
			free_cmd_ir(cmd_ir);
			error_cmd_ir_lst(minishell, head, "malloc", ERR_MALLOC);
			return (NULL);
		}
		if (tok_lst)
		{
			status = skip_pipe(&tok_lst);
			if (status == ERR_SYNTAX)
			{
				error_cmd_ir_lst(minishell, head, "newline", ERR_SYNTAX);
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

t_pipeline_ir	*parse(t_minishell *minishell, t_list *tok_lst)
{
	t_pipeline_ir	*pipeline_ir;

	pipeline_ir = ft_calloc(1, sizeof(t_pipeline_ir));
	if (!pipeline_ir)
	{
		error_cmd_ir_lst(minishell, NULL, "malloc", ERR_MALLOC);
		return (NULL);
	}
	pipeline_ir->cmd_ir_lst = get_cmd_ir_lst(minishell, tok_lst);
	if (!pipeline_ir->cmd_ir_lst)
	{
		free(pipeline_ir);
		return (NULL);
	}
	pipeline_ir->n = count_cmd_irs(pipeline_ir->cmd_ir_lst);
	return (pipeline_ir);
}
