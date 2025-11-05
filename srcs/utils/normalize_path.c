/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 23:57:34 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/04 12:39:57 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_last_component(char *path)
{
	char	*last_slash;

	if (ft_strcmp(path, "/") == 0)
		return ;
	last_slash = ft_strrchr(path, '/');
	if (last_slash && last_slash != path)
		*last_slash = '\0';
	else if (last_slash == path)
		*(last_slash + 1) = '\0';
}

static char	*append_component(char *path, char *component)
{
	char	*tmp;
	char	*result;

	if (ft_strlen(path) > 1)
	{
		tmp = ft_strjoin(path, "/");
		if (!tmp)
			return (NULL);
		result = ft_strjoin(tmp, component);
		free(tmp);
		return (result);
	}
	return (ft_strjoin(path, component));
}

static char	*add_validated_component(char *old_path, char *component,
		int *stat_failed)
{
	char		*new_path;
	struct stat	st;

	new_path = append_component(old_path, component);
	free(old_path);
	if (!new_path)
		return (NULL);
	if (stat(new_path, &st) != 0 || !S_ISDIR(st.st_mode))
	{
		*stat_failed = 1;
		free(new_path);
		return (NULL);
	}
	return (new_path);
}

static char	*reconstruct_path(char **split_path, int *stat_failed)
{
	char	*path;
	int		i;

	path = ft_strdup("/");
	if (!path)
		return (NULL);
	i = 0;
	while (split_path[i])
	{
		if (ft_strcmp(split_path[i], ".") == 0)
		{
			i++;
			continue ;
		}
		if (ft_strcmp(split_path[i], "..") == 0)
			remove_last_component(path);
		else
		{
			path = add_validated_component(path, split_path[i], stat_failed);
			if (!path)
				return (NULL);
		}
		i++;
	}
	return (path);
}

static t_normalize_status	handle_relative_path(const char *abs_path,
		char **result)
{
	if (!abs_path || abs_path[0] == '\0')
	{
		*result = ft_strdup(".");
		if (!*result)
			return (NORMALIZE_MALLOC_ERROR);
		return (NORMALIZE_SUCCESS);
	}
	*result = ft_strdup(abs_path);
	if (!*result)
		return (NORMALIZE_MALLOC_ERROR);
	return (NORMALIZE_SUCCESS);
}

t_normalize_status	normalize_path(const char *abs_path, char **result)
{
	char	**split_path;
	int		stat_failed;

	*result = NULL;
	if (!abs_path || abs_path[0] == '\0' || abs_path[0] != '/')
		return (handle_relative_path(abs_path, result));
	split_path = ft_split(abs_path, '/');
	if (!split_path)
		return (NORMALIZE_MALLOC_ERROR);
	stat_failed = 0;
	*result = reconstruct_path(split_path, &stat_failed);
	free_args(split_path);
	if (!*result && !stat_failed)
		return (NORMALIZE_MALLOC_ERROR);
	if (stat_failed)
	{
		*result = ft_strdup(abs_path);
		if (!*result)
			return (NORMALIZE_MALLOC_ERROR);
		return (NORMALIZE_STAT_FAILED);
	}
	return (NORMALIZE_SUCCESS);
}
