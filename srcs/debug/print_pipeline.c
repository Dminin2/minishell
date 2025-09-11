/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:58:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/12 00:19:08 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redir_lst(t_list *head)
{
	t_redir	*redir;
	int		i;

	printf("  Rdirections:\n");
	i = 1;
	while (head)
	{
		redir = head->content;
		printf("    [%d]\n", i);
		printf("      value : %s\n", redir->value);
		if (redir->type == R_IN)
			printf("      type  : R_IN\n");
		else if (redir->type == R_OUT)
			printf("      type  : R_OUT\n");
		else if (redir->type == R_HEREDOC)
			printf("      type  : R_HEREDOC\n");
		else if (redir->type == R_APPEND)
			printf("      type  : R_APPEND\n");
		else
			printf("      type  : null\n");
		head = head->next;
		i++;
	}
}

void	print_cmd_lst(t_list *head)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	i = 1;
	while (head)
	{
		printf("\nCommand #%d\n", i);
		cmd = head->content;
		j = 0;
		if (cmd->args)
		{
			printf("  Args:\n");
			while (cmd->args[j])
			{
				printf("  -(%s)\n", cmd->args[j]);
				j++;
			}
		}
		if (cmd->redir_lst)
			print_redir_lst(cmd->redir_lst);
		i++;
		head = head->next;
	}
}

void	print_pipeline(t_pipeline *pipeline)
{
	printf("=== pipeline ===\n");
	printf("cmd count : %d\n", pipeline->n);
	print_cmd_lst(pipeline->cmd_lst);
	printf("\n===  result  ===\n");
}
