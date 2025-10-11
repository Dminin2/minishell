/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 00:11:06 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/11 13:44:03 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_minishell *minishell, char **args, t_status *status)
{
	unsigned char	last_status;

	if (isatty(STDERR_FILENO) && isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (!args[1])
	{
		*status = SHOULD_EXIT;
		return (minishell->last_status);
	}
	if (strtouc_and_validate(args[1], &last_status))
	{
		print_error_msg_builtin("exit", args[1], BLTERR_NUM_ARG);
		*status = SHOULD_EXIT;
		return (2);
	}
	if (args[2])
	{
		print_error_msg_builtin("exit", NULL, BLTERR_MANY_ARG);
		return (1);
	}
	*status = SHOULD_EXIT;
	return ((int)last_status);
}
