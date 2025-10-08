/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:02:11 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/08 00:23:21 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_quoted(char *old, int *i)
{
	int		start;
	char	*new;

	if (old[*i] == '\"')
	{
		start = ++*i;
		while (old[*i] && old[*i] != '\"')
			(*i)++;
	}
	else
	{
		start = ++*i;
		while (old[*i] && old[*i] != '\'')
			(*i)++;
	}
	if (start == *i)
		new = ft_strdup("");
	else
		new = ft_substr(old, start, *i - start);
	if (old[*i] == '\"' || old[*i] == '\'')
		(*i)++;
	return (new);
}

char	*read_unquoted(char *old, int *i)
{
	int		start;
	char	*new;

	start = *i;
	while (old[*i] && old[*i] != '\'' && old[*i] != '\"')
		(*i)++;
	new = ft_substr(old, start, *i - start);
	return (new);
}

char	*expand_delimiter(char *old, int *is_quoted)
{
	char	*word;
	char	*new_value;
	int		i;

	i = 0;
	new_value = NULL;
	while (old[i])
	{
		// double quoteもsingle quoteも展開なし
		if (old[i] == '\'' || old[i] == '\"')
		{
			word = read_quoted(old, &i);
			*is_quoted = 1;
		}
		//$も展開なし
		else
			word = read_unquoted(old, &i);
		if (!word)
		{
			if (new_value)
				free(new_value);
			return (NULL);
		}
		if (new_value)
			new_value = ft_strjoin_and_free(new_value, word);
		else
			new_value = word;
		if (!new_value)
			return (NULL);
	}
	return (new_value);
}

char	*expand_filename(t_minishell *minishell, char *old_value,
		int *is_quoted)
{
	char	*word;
	char	*new_value;
	int		i;

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
			if (new_value)
				free(new_value);
			return (NULL);
		}
		if (new_value)
			new_value = ft_strjoin_and_free(new_value, word);
		else
			new_value = word;
		if (!new_value)
			return (NULL);
	}
	return (new_value);
}
