/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:27:13 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/03 14:53:11 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	get_env_from_line(t_env *env, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	env->key = ft_substr(line, 0, i);
	if (!env->key)
		return (ERR_MALLOC);
	if (line[i] == '\0')
		env->value = NULL;
	else
	{
		env->value = ft_strdup(line + i + 1);
		if (!env->value)
			return (ERR_MALLOC);
	}
	return (SUCCESS);
}

char	*pack_line(char *key, char *value)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	line = ft_strjoin(tmp, value);
	free(tmp);
	return (line);
}

int	is_valid_key_first_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	else
		return (0);
}

int	is_valid_key_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	else
		return (0);
}
