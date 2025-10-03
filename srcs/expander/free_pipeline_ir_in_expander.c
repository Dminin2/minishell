/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipeline_ir_in_expander.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 21:01:35 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/03 21:07:13 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args_lst_after_expand_wrapper(void *args)
{
	(void)args;
	return ;
}

void	free_cmd_ir_after_expand(t_cmd_ir *cmd_ir)
{
	if (cmd_ir)
	{
		if (cmd_ir->args_lst)
			ft_lstclear(&cmd_ir->args_lst, free_args_lst_after_expand_wrapper);
		free(cmd_ir);
	}
}
void	free_cmd_ir_after_expand_wrapper(void *cmd_ir)
{
	free_cmd_ir_after_expand((t_cmd_ir *)cmd_ir);
}

void	free_pipeline_ir_after_expand(t_pipeline_ir *pipeline_ir)
{
	if (pipeline_ir)
	{
		if (pipeline_ir->cmd_ir_lst)
			ft_lstclear(&(pipeline_ir->cmd_ir_lst),
				&free_cmd_ir_after_expand_wrapper);
		free(pipeline_ir);
	}
}
