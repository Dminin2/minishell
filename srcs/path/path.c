/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:32:03 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/06 14:03:02 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_slash(char *cmd)
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

static char	*create_full_path(t_cmd *cmd, char *path)
{
	char	*tmp;
	char	*full_path;

	if (path[0] != '\0')
		tmp = ft_strjoin(path, "/");
	else
		tmp = ft_strjoin("./", path);
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd->args[0]);
	free(tmp);
	return (full_path);
}

static t_status	search_path(t_cmd *cmd, char **paths)
{
	char		*full_path;
	int			i;
	struct stat	st_buf;

	i = 0;
	while (paths[i])
	{
		full_path = create_full_path(cmd, paths[i]);
		if (!full_path)
			return (ERR_MALLOC);
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

t_status	assign_direct_path(t_cmd *cmd)
{
	cmd->path = ft_strdup(cmd->args[0]);
	if (!cmd->path)
		return (ERR_MALLOC);
	return (SUCCESS);
}

t_status	resolve_command_path(t_cmd *cmd, t_list *env_lst)
{
	char		**paths;
	char		*path_value;
	t_status	status;

	path_value = search_env(env_lst, "PATH");
	if (!path_value || path_value[0] == '\0' || has_slash(cmd->args[0]))
		status = assign_direct_path(cmd);
	else
	{
		paths = split_path_value(path_value);
		if (!paths)
			return (ERR_MALLOC);
		status = search_path(cmd, paths);
		free_args(paths);
	}
	return (status);
}
