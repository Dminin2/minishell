/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:53:10 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/08 21:19:03 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_path_words(char *path_value)
{
	int	i;
	int	words;

	i = 0;
	words = 1;
	while (path_value[i])
	{
		if (path_value[i] == ':')
			words++;
		i++;
	}
	return (words);
}

char	*get_path_words(char *path_value, int *i)
{
	int		start;
	char	*word;

	start = *i;
	while (path_value[*i] && path_value[*i] != ':')
		(*i)++;
	word = ft_substr(path_value, start, *i - start);
	if (path_value[*i] == ':')
		(*i)++;
	return (word);
}

char	**split_path_value(char *path_value)
{
	char	**paths;
	int		words;
	int		i;
	int		j;

	words = count_path_words(path_value);
	i = 0;
	j = 0;
	paths = ft_calloc((words + 1), sizeof(char *));
	if (!paths)
		return (NULL);
	while (j < words)
	{
		paths[j] = get_path_words(path_value, &i);
		if (!paths[j])
		{
			free_args(paths);
			return (NULL);
		}
		j++;
	}
	return (paths);
}
