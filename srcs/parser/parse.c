/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:23:07 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/02 20:19:43 by aomatsud         ###   ########.fr       */
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

t_list	*get_cmd_lst(t_list *tok_lst)
{
	t_cmd		*cmd;
	t_status	status;
	t_list		*head;

	head = NULL;
	while (tok_lst)
	{
		cmd = ft_calloc(sizeof(t_cmd), 1);
		if (!cmd)
		{
			assert_error_parser(head, "malloc", ERR_SYSTEM);
			return (NULL);
		}
		status = get_simple_command(&tok_lst, cmd);
		if (status != SUCCESS)
		{
			free_cmd(cmd);
			handle_error(tok_lst, head, status);
			return (NULL);
		}
		status = add_newlst(&head, (void *)cmd);
		if (status == ERR_SYSTEM)
		{
			free_cmd(cmd);
			assert_error_parser(head, "malloc", ERR_SYSTEM);
			return (NULL);
		}
		if (tok_lst)
			status = skip_pipe(&tok_lst);
		if (status == ERR_SYNTAX)
		{
			assert_error_parser(head, "newline", ERR_SYNTAX);
			return (NULL);
		}
	}
	return (head);
}

int	count_cmds(t_list *cmd_lst)
{
	int	n;

	n = 0;
	while (cmd_lst)
	{
		n++;
		cmd_lst = cmd_lst->next;
	}
	return (n);
}

t_pipeline	*parse(t_list *tok_lst)
{
	t_pipeline	*pipeline;

	pipeline = ft_calloc(sizeof(t_pipeline), 1);
	if (!pipeline)
	{
		assert_error_parser(NULL, "malloc", ERR_SYSTEM);
		return (NULL);
	}
	pipeline->cmd_lst = get_cmd_lst(tok_lst);
	if (!pipeline->cmd_lst)
	{
		free(pipeline);
		return (NULL);
	}
	pipeline->n = count_cmds(pipeline->cmd_lst);
	return (pipeline);
}
