/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:43:55 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/02 23:11:19 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_special_word(t_minishell minishell, char *old, int *i)
{
	char	*word;

	if (old[*i] == '\'')
		word = handle_single_quote(old, i);
	else if (old[*i] == '\"')
		word = handle_double_quote(minishell, old, i);
	else
		word = expand_parameter(minishell, old, i);
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

t_status	expand_args_lst(t_minishell minishell, t_list *args_lst)
{
	char	*old_args;
	int		i;
	char	word;
	char	*new_args;

	while (args_lst)
	{
		new_args = NULL;
		old_args = args_lst->content;
		i = 0;
		while (old_args[i])
		{
			if (is_to_expand(old_args[i]))
				word = handle_special_word(minishell, old_args, &i);
			else
				word = handle_normal_word(old_args, &i);
			if (!word)
			{
				free(new_args);
				return (ERR_MALLOC);
			}
			if (new_args)
				new_args = ft_strjoin_and_free(new_args, word);
			else
				new_args = word;
			if (!new_args)
				return (ERR_MALLOC);
		}
		free(old_args);
		args_lst->content = new_args;
		args_lst = args_lst->next;
	}
	return (SUCCESS);
}
