/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:58:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/16 01:51:38 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_lst(t_list *head, int fd)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	i = 1;
	while (head)
	{
		ft_dprintf(fd, "\nCommand #%d\n", i);
		cmd = head->content;
		j = 0;
		if (cmd->args)
		{
			ft_dprintf(fd, "  Args:\n");
			while (cmd->args[j])
			{
				ft_dprintf(fd, "  -(%s)\n", cmd->args[j]);
				j++;
			}
		}
		if (cmd->redir_lst)
			print_redir_lst(cmd->redir_lst, fd);
		i++;
		head = head->next;
	}
}

void	print_pipeline(t_pipeline *pipeline, int fd)
{
	ft_dprintf(fd, "=== pipeline ===\n");
	ft_dprintf(fd, "cmd count : %d\n", pipeline->n);
	print_cmd_lst(pipeline->cmd_lst, fd);
	ft_dprintf(fd, "\n");
}
