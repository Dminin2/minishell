/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 23:57:34 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/30 21:49:14 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_component(char **components, int *count, char *component)
{
	if (ft_strcmp(component, ".") == 0)
		return ;
	if (ft_strcmp(component, "..") == 0)
	{
		if (*count > 0)
			(*count)--;
		return ;
	}
	components[*count] = component;
	(*count)++;
}

static char	*reconstruct_path(char **components, int count, int *stat_failed)
{
	char		*path;
	char		*tmp;
	int			i;
	struct stat	st;

	path = ft_strdup("/");
	if (!path)
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (ft_strlen(path) > 1)
		{
			tmp = ft_strjoin(path, "/");
			free(path);
			if (!tmp)
				return (NULL);
			path = tmp;
		}
		tmp = ft_strjoin(path, components[i]);
		free(path);
		if (!tmp)
			return (NULL);
		path = tmp;
		if (!(stat(path, &st) == 0 && S_ISDIR(st.st_mode)))
		{
			*stat_failed = 1;
			free(path);
			return (NULL);
		}
		i++;
	}
	return (path);
}

t_normalize_status	normalize_path(const char *abs_path, char **result)
{
	char	**split_path;
	char	**components;
	int		i;
	int		count;
	int		stat_failed;

	if (!abs_path || abs_path[0] == '\0')
	{
		*result = ft_strdup(".");
		if (!*result)
			return (NORMALIZE_MALLOC_ERROR);
		return (NORMALIZE_SUCCESS);
	}
	if (abs_path[0] != '/')
	{
		*result = ft_strdup(abs_path);
		if (!*result)
			return (NORMALIZE_MALLOC_ERROR);
		return (NORMALIZE_SUCCESS);
	}
	split_path = ft_split(abs_path, '/');
	if (!split_path)
		return (NORMALIZE_MALLOC_ERROR);
	i = 0;
	while (split_path[i])
		i++;
	components = ft_calloc(i, sizeof(char *));
	if (!components)
	{
		free_args(split_path);
		return (NORMALIZE_MALLOC_ERROR);
	}
	count = 0;
	i = 0;
	while (split_path[i])
	{
		process_component(components, &count, split_path[i]);
		i++;
	}
	stat_failed = 0;
	*result = reconstruct_path(components, count, &stat_failed);
	free(components);
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
