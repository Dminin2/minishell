/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:02:11 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/07 13:12:36 by aomatsud         ###   ########.fr       */
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

char	*expand_delimiter(char *old, int *i, int *is_quoted)
{
	char	*word;

	// double quoteもsigle quoteも展開なし
	if (old[*i] == '\'' || old[*i] == '\"')
	{
		word = read_quoted(old, i);
		*is_quoted = 1;
	}
	//$も展開なし
	else
		word = read_unquoted(old, i);
	return (word);
}

char	*expand_filename(t_minishell *minishell, char *old_value, int *i,
		int *is_quoted)
{
	char	*word;

	if (is_to_expand(old_value[*i]))
		word = handle_special_word(minishell, old_value, i, is_quoted);
	else
		word = handle_normal_word(old_value, i);
	return (word);
}

char	*get_new_value(t_minishell *minishell, t_redir *redir, int *is_quoted)
{
	int		i;
	char	*word;
	char	*new_value;
	char	*old_value;

	old_value = redir->value;
	i = 0;
	new_value = NULL;
	while (old_value[i])
	{
		if (redir->type == R_HEREDOC)
			word = expand_delimiter(old_value, &i, is_quoted);
		else
			word = expand_filename(minishell, old_value, &i, is_quoted);
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

t_status	expand_redir_lst(t_minishell *minishell, t_list *redir_lst,
		t_redir_err *err)
{
	char	*new_value;
	t_redir	*redir;
	int		is_quoted;

	while (redir_lst)
	{
		is_quoted = 0;
		redir = redir_lst->content;
		new_value = get_new_value(minishell, redir, &is_quoted);
		if (!new_value)
			return (ERR_MALLOC);
		if (redir->type != R_HEREDOC && !is_quoted && new_value[0] == '\0')
		{
			free(new_value);
			err->redir_err = redir;
			err->status = ERR_AMB_REDIR;
			return (ERR_AMB_REDIR);
		}
		free(redir->value);
		redir->value = new_value;
		redir_lst = redir_lst->next;
	}
	return (SUCCESS);
}
