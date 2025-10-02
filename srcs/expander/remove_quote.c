/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:41:53 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/02 21:58:00 by hmaruyam         ###   ########.fr       */
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
	char	*tmp;

	tmp = ft_substr(old, start, end - start);
	if (!tmp)
	{
		free(new);
		return (NULL);
	}
	if (new)
		new = ft_strjoin_and_free(new, tmp);
	else
		new = tmp;
	return (new);
}

char	*add_env_value(t_minishell *minishell, int *i, char *new, char *old)
{
	char	*tmp;

	tmp = expand_parameter(minishell, old, i);
	if (!tmp)
	{
		if (new)
			free(new);
		return (NULL);
	}
	if (new)
		new = ft_strjoin_and_free(new, tmp);
	else
		new = tmp;
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
			new = add_env_value(minishell, i, new, old);
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
