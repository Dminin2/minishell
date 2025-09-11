/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:32:03 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/11 20:03:46 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	find_path_indexdex(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (i);
}

t_status	search_path(t_cmd *cmd, char **paths)
{
	char		*full_path;
	char		*tmp;
	int			i;
	struct stat	st_buf;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (ERR_SYSTEM);
		full_path = ft_strjoin(tmp, cmd->args[0]);
		free(tmp);
		if (!full_path)
			return (ERR_SYSTEM);
		if (stat(full_path, &st_buf) != -1 && !S_ISDIR(st_buf.st_mode))
		{
			cmd->path = full_path;
			return (SUCCESS);
		}
		free(full_path);
		i++;
	}
	return (ERR_CMD_NOT_FOUND);
}

t_status	assign_direct_path(t_cmd *cmd, int path_index, char **envp)
{
	t_status	status;

	if (!cmd->args[0])
	{
		if (!envp[path_index])
			status = ERR_NOT_VALID_PATH;
		else
			status = ERR_CMD_NOT_FOUND;
	}
	else
	{
		cmd->path = ft_strdup(cmd->args[0]);
		if (!cmd->path)
			return (ERR_SYSTEM);
		status = SUCCESS;
	}
	return (status);
}

t_status	resolve_command_path(t_cmd *cmd, char **envp)
{
	char		**paths;
	int			path_index;
	t_status	status;

	path_index = find_path_indexdex(envp);
	if (!envp[path_index] || !cmd->args[0] || has_slash(cmd->args[0]))
		status = assign_direct_path(cmd, path_index, envp);
	else
	{
		paths = ft_split(&envp[path_index][5], ':');
		if (!paths)
			return (ERR_SYSTEM);
		status = search_path(cmd, paths);
		free_args(paths);
	}
	return (status);
}
