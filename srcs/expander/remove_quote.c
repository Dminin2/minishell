/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:41:53 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/03 00:13:41 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_single_quote(char *old, int *pos)
{
	int		start;
	char	*new;

	start = ++*pos;
	while (old[*pos] && old[*pos] != '\'')
		(*pos)++;
	if (start == *pos)
		new = ft_strdup("");
	else
		new = ft_substr(old, start, *pos - start);
	if (old[*pos] == '\'')
		(*pos)++;
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

char	*append_env_parameter(t_minishell *minishell, int *pos, char *new,
		char *old)
{
	char	*expand_str;

	expand_str = expand_parameter(minishell, old, pos);
	if (!expand_str)
	{
		free(new);
		return (NULL);
	}
	new = create_new_value(new, expand_str);
	return (new);
}

char	*handle_double_quote(t_minishell *minishell, char *old, int *pos)
{
	char	*new;
	int		start;

	start = ++(*pos);
	new = NULL;
	while (old[*pos] && old[*pos] != '\"')
	{
		if (old[*pos] == '$')
		{
			if (start != *pos)
			{
				new = add_normal_words(start, *pos, new, old);
				if (!new)
					return (NULL);
			}
			new = append_env_parameter(minishell, pos, new, old);
			if (!new)
				return (NULL);
			start = *pos;
		}
		else
			(*pos)++;
	}
	if (start != *pos)
		new = add_normal_words(start, *pos, new, old);
	else if (!new)
		new = ft_strdup("");
	if (old[*pos] == '\"')
		(*pos)++;
	return (new);
}
