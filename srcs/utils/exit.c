/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:45:13 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/02 20:23:10 by aomatsud         ###   ########.fr       */
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
}

void	assert_error(t_list *lst, char *context, t_status status)
{
	print_error_msg(context, status);
	ft_lstclear(&lst, free_token_wrapper);
}

void	assert_error_parser(t_list *lst, char *context, t_status status)
{
	print_error_msg(context, status);
	ft_lstclear(&lst, free_cmd_wrapper);
}

void	exit_error(t_cmd *cmd, char *context, t_status status, int exit_status)
{
	print_error_msg(context, status);
	free_cmd(cmd);
	exit(exit_status);
}
