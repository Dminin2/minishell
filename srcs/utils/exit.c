/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:45:13 by aomatsud          #+#    #+#             */
/*   Updated: 2025/08/18 20:44:19 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_msg(char *context)
{
	dprintf(STDERR_FILENO, "minishell: %s: %s\n", context, strerror(errno));
}

void	exit_error(t_cmd *cmd, char *context, t_status status, int exit_status)
{
	if (status == ERR_SYSTEM)
		print_error_msg(context);
	free_cmd(cmd);
	exit(exit_status);
}
