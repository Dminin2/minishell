/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:12:36 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/05 18:12:56 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command_type	scan_command_type(t_cmd *cmd)
{
	t_command_type	type;

	if (cmd->args)
	{
		if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
			type = BLT_ECHO;
		else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
			type = BLT_CD;
		else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
			type = BLT_PWD;
		else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
			type = BLT_EXPORT;
		else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
			type = BLT_UNSET;
		else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
			type = BLT_ENV;
		else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
			type = BLT_EXIT;
		else
			type = EXTERNAL;
	}
	else
		type = NO_CMD;
	return (type);
}

void	execute_builtin(t_minishell *minishell, t_cmd *cmd, t_command_type type)
{
	(void)cmd;
	if (type == BLT_ECHO)
		printf("todo:echo\n");
	else if (type == BLT_CD)
		printf("todo:cd\n");
	else if (type == BLT_PWD)
		minishell->last_status = builtin_pwd(minishell);
	else if (type == BLT_EXPORT)
		printf("todo:export\n");
	else if (type == BLT_UNSET)
		printf("todo:unset\n");
	else if (type == BLT_ENV)
		printf("todo:env\n");
	else if (type == BLT_EXIT)
		printf("todo:exit\n");
}
