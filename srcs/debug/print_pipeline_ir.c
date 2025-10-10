/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pipeline_ir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:38:51 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/09 22:25:40 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args_lst(t_list *head)
{
	char	*args;

	while (head)
	{
		args = head->content;
		printf("    -(%s)\n", args);
		head = head->next;
	}
}

void	print_cmd_ir_lst(t_list *head)
{
	int			i;
	t_cmd_ir	*cmd_ir;

	i = 1;
	while (head)
	{
		printf("\nCommand #%d\n", i);
		cmd_ir = head->content;
		if (cmd_ir->args_lst)
		{
			printf("  Args:\n");
			print_args_lst(cmd_ir->args_lst);
		}
		if (cmd_ir->redir_lst)
			print_redir_lst(cmd_ir->redir_lst);
		i++;
		head = head->next;
	}
}

void	print_pipeline_ir(t_pipeline_ir *pipeline_ir)
{
	printf("=== pipeline_ir ===\n");
	printf("cmd count : %d\n", pipeline_ir->n);
	print_cmd_ir_lst(pipeline_ir->cmd_ir_lst);
	printf("\n");
}
