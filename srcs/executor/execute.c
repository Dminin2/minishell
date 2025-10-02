/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:38:36 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/03 00:38:54 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_pipeline *pipeline, char **envp)
{
	if (pipeline->n == 1 && is_builtin((t_cmd *)(pipeline->cmd_lst->content)))
		run_builtin_in_parent(pipeline);
	else
		child_process(pipeline, envp);
}
