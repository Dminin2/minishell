/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:43:55 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/02 22:44:54 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_special_word(t_minishell *minishell, char *old, int *i,
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

char	*handle_normal_word(char *old, int *i)
{
	int		start;
	char	*new;

	start = *i;
	while (old[*i] && !is_to_expand(old[*i]))
		(*i)++;
	new = ft_substr(old, start, *i - start);
	return (new);
}

t_status	expand_args_lst(t_minishell *minishell, t_list *args_lst)
{
	char		*old_value;
	char		*new_value;
	int			is_quoted;
	t_status	status;

	while (args_lst)
	{
		is_quoted = 0;
		new_value = NULL;
		old_value = args_lst->content;
		status = expand_string(minishell, old_value, &new_value, &is_quoted);
		if (status == ERR_MALLOC)
			return (status);
		if (!is_quoted && new_value[0] == '\0')
		{
			free(new_value);
			new_value = NULL;
		}
		free(old_value);
		args_lst->content = new_value;
		args_lst = args_lst->next;
	}
	return (SUCCESS);
}
