/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_parameter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:42:36 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/04 11:56:54 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_last_status(t_minishell *minishell, int *pos)
{
	char	*value;

	value = ft_itoa(minishell->last_status);
	*pos += 2;
	return (value);
}

static char	*not_expand(int *pos)
{
	char	*value;

	value = ft_strdup("$");
	(*pos)++;
	return (value);
}

char	*expand_parameter(t_minishell *minishell, char *args, int *pos)
{
	char	*key;
	char	*value;
	int		start;

	if (args[*pos + 1] == '?')
		value = expand_last_status(minishell, pos);
	else if (!args[*pos + 1] || !is_valid_key_first_char(args[*pos + 1]))
		value = not_expand(pos);
	else
	{
		start = ++*pos;
		while (args[*pos] && is_valid_key_char(args[*pos]))
			(*pos)++;
		key = ft_substr(args, start, *pos - start);
		if (!key)
			return (NULL);
		value = search_env(minishell->env_lst, key);
		free(key);
		if (value)
			value = ft_strdup(value);
		else
			value = ft_strdup("");
	}
	return (value);
}
