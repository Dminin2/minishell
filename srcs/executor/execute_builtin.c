/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:12:36 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/03 00:34:37 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		printf("todo:echo\n");
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		printf("todo:cd\n");
	else if (ft_strncmp(cmd->args[0], "pwd", 3) == 0)
		printf("todo:pwd\n");
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		printf("todo:export\n");
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		printf("todo:unset\n");
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		printf("todo:env\n");
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		printf("todo:exit\n");
	//本来はexit_statusを返す
	return (0);
}
