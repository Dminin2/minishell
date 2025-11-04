/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:55:02 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/04 11:57:35 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_special_word(t_minishell *minishell, char *old, int *i,
		int *is_quoted)
{
	char	*word;

	if (old[*i] == '$')
		word = expand_parameter(minishell, old, i);
	else
	{
		if (old[*i] == '\'')
			word = handle_single_quote(old, i);
		else
			word = handle_double_quote(minishell, old, i);
		*is_quoted = 1;
	}
	return (word);
}

static char	*handle_normal_word(char *old, int *i)
{
	int		start;
	char	*new;

	start = *i;
	while (old[*i] && !is_to_expand(old[*i]))
		(*i)++;
	new = ft_substr(old, start, *i - start);
	return (new);
}

char	*expand_string(t_minishell *minishell, char *old_value, int *is_quoted)
{
	int		i;
	char	*word;
	char	*new_value;

	i = 0;
	new_value = NULL;
	while (old_value[i])
	{
		if (is_to_expand(old_value[i]))
			word = handle_special_word(minishell, old_value, &i, is_quoted);
		else
			word = handle_normal_word(old_value, &i);
		if (!word)
		{
			free(new_value);
			return (NULL);
		}
		new_value = create_new_value(new_value, word);
		if (!new_value)
			return (NULL);
	}
	return (new_value);
}
