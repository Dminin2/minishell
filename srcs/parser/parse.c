/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:23:07 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/07 00:34:05 by aomatsud         ###   ########.fr       */
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
			return (handle_error(minishell, NULL, &head, ERR_MALLOC));
		status = get_simple_command(&tok_lst, cmd_ir);
		if (status != SUCCESS)
		{
			free_cmd_ir(cmd_ir);
			return (handle_error(minishell, tok_lst, &head, status));
		}
		if (add_newlst(&head, (void *)cmd_ir) == ERR_MALLOC)
		{
			free_cmd_ir(cmd_ir);
			return (handle_error(minishell, NULL, &head, ERR_MALLOC));
		}
		if (tok_lst && skip_pipe(&tok_lst) == ERR_SYNTAX)
			return (handle_error(minishell, NULL, &head, ERR_SYNTAX));
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
