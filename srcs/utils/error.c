/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:40:59 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/06 10:27:40 by hmaruyam         ###   ########.fr       */
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
	else if (status == ERR_AMB_REDIR)
		ft_dprintf_buf(STDERR_FILENO, "minishell: %s: %s\n", context, AMB_ERR);
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
			ft_dprintf_buf(STDERR_FILENO, "minishell: %s: %s\n", cmd, HOME_ERR);
		else if (error == BLTERR_NO_SET_OLDPWD)
			ft_dprintf_buf(STDERR_FILENO, "minishell: %s: %s\n", cmd,
				OLDPWD_ERR);
		else if (error == BLTERR_MANY_ARG)
			ft_dprintf_buf(STDERR_FILENO, "minishell: %s: %s\n", cmd, ARG_ERR);
	}
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
