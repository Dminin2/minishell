/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:38:36 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/05 09:44:45 by hmaruyam         ###   ########.fr       */
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
