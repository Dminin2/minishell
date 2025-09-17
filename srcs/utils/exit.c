/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:45:13 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/16 16:35:43 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_msg(char *context, t_status status)
{
	if (status == ERR_SYSTEM)
		dprintf(STDERR_FILENO, "minishell: %s: %s\n", context, strerror(errno));
	else if (status == ERR_CMD_NOT_FOUND)
		dprintf(STDERR_FILENO, "minishell: %s: %s\n", context,
			"command not found");
	else if (status == ERR_NOT_VALID_PATH)
		dprintf(STDERR_FILENO, "minishell: %s: %s\n", context,
			"No such file or directory");
	else if (status == ERR_SYNTAX)
		dprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token `%s'\n", context);
	else if (status == ERR_FILE)
		dprintf(STDERR_FILENO, "minishell: %s: %s\n", context, strerror(errno));
	else if (status == ERR_ERRNO)
		dprintf(STDERR_FILENO, "minishell: %s: %s\n", context, strerror(errno));
	else if (status == ERR_ISDIR)
		dprintf(STDERR_FILENO, "minishell: %s: is a directory\n", context);
}

void	assert_error(t_list *lst, char *context, t_status status)
{
	print_error_msg(context, status);
	ft_lstclear(&lst, free_token_wrapper);
}

void	assert_error_parser(t_list *lst, char *context, t_status status)
{
	print_error_msg(context, status);
	ft_lstclear(&lst, free_cmd_ir_wrapper);
}

void	assert_error_parent(t_pipeline *pipeline, char *context,
		t_status status)
{
	print_error_msg(context, status);
	free_pipeline(pipeline);
}

void	assert_error_env_init(t_list *env_lst, char *context, t_status status)
{
	print_error_msg(context, status);
	ft_lstclear(&env_lst, free_env_wrapper);
}

void	exit_error(t_pipeline *pipeline, char *context, t_status status,
		int exit_status)
{
	print_error_msg(context, status);
	free_pipeline(pipeline);
	exit(exit_status);
}
