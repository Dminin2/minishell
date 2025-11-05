/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 23:45:13 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/05 14:36:30 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_msg(char *context, t_status status)
{
	if (status == ERR_CMD_NOT_FOUND)
		ft_dprintf_buf(STDERR_FILENO, "minishell: %s: %s\n", context, CMD_ERR);
	else if (status == ERR_NOT_VALID_PATH)
		ft_dprintf_buf(STDERR_FILENO, "minishell: %s: %s\n", context, VLD_ERR);
	else if (status == ERR_SYNTAX)
		ft_dprintf_buf(STDERR_FILENO, "minishell: %s `%s'\n", SYN_ERR, context);
	else if (status == ERR_FILE)
		ft_dprintf_buf(STDERR_FILENO, "minishell: %s: %s\n", context,
			strerror(errno));
	else if (status == ERR_AMB_REDIR)
		ft_dprintf_buf(STDERR_FILENO, "minishell: %s: %s\n", AMB_ERR, context);
	else if (status == ERR_ERRNO)
		ft_dprintf_buf(STDERR_FILENO, "minishell: %s: %s\n", context,
			strerror(errno));
	else if (status == ERR_ISDIR)
		ft_dprintf_buf(STDERR_FILENO, "minishell: %s: Is a directory\n",
			context);
	else if (status == ERR_HEREDOC)
		ft_dprintf_buf(STDERR_FILENO, "\nminishell: %s `%s')\n", HD_ERR,
			context);
	else if (status == ERR_QUOTE)
		ft_dprintf_buf(STDERR_FILENO, "minishell: %s %s\n", QUOTE_ERR, context);
	else
		ft_dprintf_buf(STDERR_FILENO, "minishell: %s: %s\n", context,
			strerror(errno));
}

void	print_error_msg_builtin(char *cmd, char *context, t_blt_error error)
{
	if (context)
	{
		if (error == BLTERR_ERRNO)
			ft_dprintf_buf(STDERR_FILENO, "minishell: %s: %s: %s\n", cmd,
				context, strerror(errno));
		else if (error == BLTERR_NUM_ARG)
			ft_dprintf_buf(STDERR_FILENO, "minishell: %s: %s: %s\n", cmd,
				context, NUMARG_ERR);
		else if (error == BLTERR_NOT_VALID)
			ft_dprintf_buf(STDERR_FILENO, "minishell: %s: `%s': %s\n", cmd,
				context, ENV_ERR);
	}
	else
	{
		if (error == BLTERR_ERRNO)
			ft_dprintf_buf(STDERR_FILENO, "minishell: %s: %s\n", cmd,
				strerror(errno));
		else if (error == BLTERR_NO_SET_HOME)
			ft_dprintf_buf(STDERR_FILENO, "minishell: %s: %s\n", HOME_ERR, cmd);
		else if (error == BLTERR_NO_SET_OLDPWD)
			ft_dprintf_buf(STDERR_FILENO, "minishell: %s: %s\n", OLDPWD_ERR,
				cmd);
		else if (error == BLTERR_MANY_ARG)
			ft_dprintf_buf(STDERR_FILENO, "minishell: %s: %s\n", ARG_ERR, cmd);
	}
}

static int	get_exit_status(t_status status)
{
	if (status == SUCCESS)
		return (0);
	else if (status == ERR_SYNTAX || status == ERR_QUOTE)
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

int	error_lst(t_list *lst, char *context, t_status status, void (*del)(void *))
{
	print_error_msg(context, status);
	ft_lstclear(&lst, del);
	return (get_exit_status(status));
}

int	error_parent(t_pipeline *pipeline, char *context, t_status status)
{
	print_error_msg(context, status);
	free_pipeline(pipeline);
	return (get_exit_status(status));
}

void	exit_error(t_minishell *minishell, t_pipeline *pipeline, char *context,
		t_status status)
{
	print_error_msg(context, status);
	free_pipeline(pipeline);
	ft_lstclear(&(minishell->env_lst), free_env_wrapper);
	free(minishell->cwd);
	exit(get_exit_status(status));
}

void	exit_success(t_minishell *minishell, t_pipeline *pipeline)
{
	free_pipeline(pipeline);
	ft_lstclear(&(minishell->env_lst), free_env_wrapper);
	free(minishell->cwd);
	exit(0);
}
