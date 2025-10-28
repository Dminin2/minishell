/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 23:57:34 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/28 23:57:44 by hmaruyam         ###   ########.fr       */
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

static char	*reconstruct_path(char **components, int count)
{
	char	*path;
	char	*tmp;
	int		i;

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
		i++;
	}
	return (path);
}

char	*normalize_path(const char *abs_path)
{
	char	**split_path;
	char	**components;
	char	*normalized_path;
	int		i;
	int		count;

	split_path = ft_split(abs_path, '/');
	if (!split_path)
		return (NULL);
	i = 0;
	while (split_path[i])
		i++;
	components = ft_calloc(i, sizeof(char *));
	if (!components)
	{
		free_args(split_path);
		return (NULL);
	}
	count = 0;
	i = 0;
	while (split_path[i])
	{
		process_component(components, &count, split_path[i]);
		i++;
	}
	normalized_path = reconstruct_path(components, count);
	free(components);
	free_args(split_path);
	return (normalized_path);
}
