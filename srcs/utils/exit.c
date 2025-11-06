/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:45:13 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/06 13:03:15 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exit_status(t_status status)
{
	if (status == SUCCESS)
		return (0);
	else if (status == ERR_SYNTAX || status == ERR_QUOTE
		|| status == ERR_MALLOC)
		return (2);
	else if (status == ERR_CMD_NOT_FOUND || status == ERR_NOT_VALID_PATH
		|| status == ERR_ENOENT)
		return (127);
	else if (status == ERR_ISDIR || status == ERR_EACCES
		|| status == ERR_ENOTDIR || status == ERR_EXECVE_OTHER)
		return (126);
	else
		return (1);
}

void	exit_error(t_minishell *minishell, t_pipeline *pipeline, char *context,
		t_status status)
{
	print_error_msg(context, status);
	free_pipeline(pipeline);
	ft_lstclear(&(minishell->env_lst), free_env_wrapper);
	free(minishell->cwd);
	if (!isatty(STDIN_FILENO))
		get_next_line(-1);
	exit(get_exit_status(status));
}

void	exit_success(t_minishell *minishell, t_pipeline *pipeline)
{
	free_pipeline(pipeline);
	ft_lstclear(&(minishell->env_lst), free_env_wrapper);
	free(minishell->cwd);
	if (!isatty(STDIN_FILENO))
		get_next_line(-1);
	exit(0);
}
