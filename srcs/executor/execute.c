/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:38:36 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/09 13:57:42 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_minishell *minishell, t_pipeline *pipeline)
{
	t_command_type	type;

	if (pipeline->n == 1)
	{
		type = scan_command_type((t_cmd *)(pipeline->cmd_lst->content));
		if (type != EXTERNAL)
		{
			run_builtin_in_parent(minishell, pipeline, type);
			return ;
		}
	}
	child_process(minishell, pipeline);
}
