/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 00:11:06 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/14 13:21:47 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_minishell *minishell, char **args, int cmd_count)
{
	unsigned char	last_status;

	if (isatty(STDERR_FILENO) && isatty(STDIN_FILENO) && cmd_count == 1)
		printf("exit\n");
	if (!args[1])
	{
		minishell->should_exit = 1;
		return (minishell->last_status);
	}
	if (strtouc_and_validate(args[1], &last_status))
	{
		print_error_msg_builtin("exit", args[1], BLTERR_NUM_ARG);
		minishell->should_exit = 1;
		return (2);
	}
	if (args[2])
	{
		print_error_msg_builtin("exit", NULL, BLTERR_MANY_ARG);
		return (1);
	}
	minishell->should_exit = 1;
	return ((int)last_status);
}
