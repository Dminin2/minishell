/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:45:13 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/06 00:57:20 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_msg(char *context, t_status status)
{
	if (status == ERR_CMD_NOT_FOUND)
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
	else
		dprintf(STDERR_FILENO, "minishell: %s: %s\n", context, strerror(errno));
}

void	print_error_msg_builtin(char *cmd, char *context, t_blt_error error)
{
	if (context)
	{
		if (error == BLTERR_ERRNO)
			dprintf(STDERR_FILENO, "minishell: %s: %s: %s\n", cmd, context,
				strerror(errno));
	}
	else
	{
		if (error == BLTERR_ERRNO)
			dprintf(STDERR_FILENO, "minishell: %s: %s\n", cmd, strerror(errno));
	}
}

void	assert_error_lst(t_list *lst, char *context, t_status status,
		void (*del)(void *))
{
	print_error_msg(context, status);
	ft_lstclear(&lst, del);
}

void	assert_error_parent(t_pipeline *pipeline, char *context,
		t_status status)
{
	print_error_msg(context, status);
	free_pipeline(pipeline);
}

void	exit_error(t_pipeline *pipeline, char *context, t_status status,
		int exit_status)
{
	print_error_msg(context, status);
	free_pipeline(pipeline);
	exit(exit_status);
}
