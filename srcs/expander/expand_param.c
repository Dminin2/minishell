/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:42:36 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/26 22:36:59 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_last_status(t_minishell minishell, int *i)
{
	char	*value;

	value = ft_itoa(minishell.last_status);
	*i += 2;
	return (value);
}

char	*not_expand(int *i)
{
	char	*value;

	value = ft_strdup("$");
	(*i)++;
	return (value);
}

char	*expand_parameter(t_minishell minishell, char *args, int *i)
{
	char	*key;
	char	*value;
	int		start;

	if (args[*i + 1] == '?')
		value = expand_last_status(minishell, i);
	else if (!args[*i + 1] || !is_valid_key_first_char(args[*i + 1]))
		value = not_expand(i);
	else
	{
		start = ++*i;
		while (args[*i] && is_valid_key_char(args[*i]))
			(*i)++;
		key = ft_substr(args, start, *i - start);
		if (!key)
			return (NULL);
		value = search_env(minishell.env_lst, key);
		free(key);
		if (value)
			value = ft_strdup(value);
		else
			value = ft_strdup("");
	}
	return (value);
}
