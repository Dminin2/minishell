/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pipeline_ir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 12:38:51 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/11 15:36:54 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args_lst(t_list *head, int fd)
{
	char	*args;

	while (head)
	{
		args = head->content;
		dprintf(fd, "    -(%s)\n", args);
		head = head->next;
	}
}

void	print_cmd_ir_lst(t_list *head, int fd)
{
	int			i;
	t_cmd_ir	*cmd_ir;

	i = 1;
	while (head)
	{
		dprintf(fd, "\nCommand #%d\n", i);
		cmd_ir = head->content;
		if (cmd_ir->args_lst)
		{
			dprintf(fd, "  Args:\n");
			print_args_lst(cmd_ir->args_lst, fd);
		}
		if (cmd_ir->redir_lst)
			print_redir_lst(cmd_ir->redir_lst, fd);
		i++;
		head = head->next;
	}
}

void	print_pipeline_ir(t_pipeline_ir *pipeline_ir, int fd)
{
	dprintf(fd, "=== pipeline_ir ===\n");
	dprintf(fd, "cmd count : %d\n", pipeline_ir->n);
	print_cmd_ir_lst(pipeline_ir->cmd_ir_lst, fd);
	dprintf(fd, "\n");
}
