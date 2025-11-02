/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:41:53 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/02 19:20:47 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_single_quote(char *old, int *i)
{
	int		start;
	char	*new;

	start = ++*i;
	while (old[*i] && old[*i] != '\'')
		(*i)++;
	if (start == *i)
		new = ft_strdup("");
	else
		new = ft_substr(old, start, *i - start);
	if (old[*i] == '\'')
		(*i)++;
	return (new);
}

char	*add_normal_words(int start, int end, char *new, char *old)
{
	char	*sub_str;

	sub_str = ft_substr(old, start, end - start);
	if (!sub_str)
	{
		free(new);
		return (NULL);
	}
	if (new)
		new = ft_strjoin_and_free(new, sub_str);
	else
		new = sub_str;
	return (new);
}

char	*process_env_key_value_value(t_minishell *minishell, int *i, char *new,
		char *old)
{
	char	*expand_str;

	expand_str = expand_parameter(minishell, old, i);
	if (!expand_str)
	{
		if (new)
			free(new);
		return (NULL);
	}
	if (new)
		new = ft_strjoin_and_free(new, expand_str);
	else
		new = expand_str;
	return (new);
}

char	*handle_double_quote(t_minishell *minishell, char *old, int *i)
{
	char	*new;
	int		copied_pos;

	copied_pos = ++(*i);
	new = NULL;
	while (old[*i] && old[*i] != '\"')
	{
		if (old[*i] == '$')
		{
			if (copied_pos != *i)
			{
				new = add_normal_words(copied_pos, *i, new, old);
				if (!new)
					return (NULL);
			}
			new = process_env_key_value_value(minishell, i, new, old);
			if (!new)
				return (NULL);
			copied_pos = *i;
		}
		else
			(*i)++;
	}
	if (copied_pos != *i)
		new = add_normal_words(copied_pos, *i, new, old);
	else if (!new)
		new = ft_strdup("");
	if (old[*i] == '\"')
		(*i)++;
	return (new);
}
