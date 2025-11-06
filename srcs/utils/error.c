/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:40:59 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/06 16:15:38 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_env_lst(t_minishell *minishell, t_list *lst, char *context,
		t_status status)
{
	print_error_msg(context, status);
	ft_lstclear(&lst, free_env_wrapper);
	minishell->last_status = get_exit_status(status);
	if (status == ERR_MALLOC)
		minishell->should_exit = 1;
}

void	error_cmd_lst(t_minishell *minishell, t_list *lst, char *context,
		t_status status)
{
	print_error_msg(context, status);
	ft_lstclear(&lst, free_cmd_wrapper);
	minishell->last_status = get_exit_status(status);
	if (status == ERR_MALLOC)
		minishell->should_exit = 1;
}

void	error_token_lst(t_minishell *minishell, t_list *lst, char *context,
		t_status status)
{
	print_error_msg(context, status);
	ft_lstclear(&lst, free_token_wrapper);
	minishell->last_status = get_exit_status(status);
	if (status == ERR_MALLOC)
		minishell->should_exit = 1;
}

void	error_cmd_ir_lst(t_minishell *minishell, t_list *lst, char *context,
		t_status status)
{
	print_error_msg(context, status);
	ft_lstclear(&lst, free_cmd_ir_wrapper);
	minishell->last_status = get_exit_status(status);
	if (status == ERR_MALLOC)
		minishell->should_exit = 1;
}

void	error_parent(t_minishell *minishell, t_pipeline *pipeline,
		char *context, t_status status)
{
	print_error_msg(context, status);
	free_pipeline(pipeline);
	minishell->last_status = get_exit_status(status);
	if (status == ERR_MALLOC)
		minishell->should_exit = 1;
}
