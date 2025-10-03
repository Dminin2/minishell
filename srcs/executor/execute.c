/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:38:36 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/03 21:55:40 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_pipeline *pipeline, char **envp)
{
	t_command_type	type;

	if (pipeline->n == 1)
	{
		type = scan_command_type((t_cmd *)(pipeline->cmd_lst->content));
		if (type != EXTERNAL)
		{
			run_builtin_in_parent(pipeline);
			return ;
		}
	}
	child_process(pipeline, envp);
}
