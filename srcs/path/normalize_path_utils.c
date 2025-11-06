/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_path_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:09:36 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/05 14:10:37 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_last_component(char *path)
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

char	*append_component(char *path, char *component)
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
