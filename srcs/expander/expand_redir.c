/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:02:11 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/02 22:36:26 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_quoted(char *old, int *i)
{
	int		start;
	char	*new;
	char	quote;

	quote = old[*i];
	start = ++*i;
	while (old[*i] && old[*i] != quote)
		(*i)++;
	if (start == *i)
		new = ft_strdup("");
	else
		new = ft_substr(old, start, *i - start);
	if (old[*i] == quote)
		(*i)++;
	return (new);
}

static char	*read_unquoted(char *old, int *i)
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
		if (old[i] == '\'' || old[i] == '\"')
		{
			word = read_quoted(old, &i);
			*is_quoted = 1;
		}
		else
			word = read_unquoted(old, &i);
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

char	*expand_filename(t_minishell *minishell, char *old_value,
		int *is_quoted)
{
	char		*new_value;
	t_status	status;

	new_value = NULL;
	status = expand_string(minishell, old_value, &new_value, is_quoted);
	if (status == ERR_MALLOC)
		return (NULL);
	return (new_value);
}
