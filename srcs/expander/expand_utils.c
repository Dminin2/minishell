/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:31:17 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/02 22:43:52 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!res)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	free(s2);
	return (res);
}

int	is_to_expand(char c)
{
	if (c == '\'' || c == '\"' || c == '$')
		return (1);
	else
		return (0);
}

char	*create_new_value(char *new_value, char *word)
{
	if (new_value)
		return (ft_strjoin_and_free(new_value, word));
	else
		return (word);
}

t_status	expand_string(t_minishell *minishell, char *old_value,
		char **new_value, int *is_quoted)
{
	int		i;
	char	*word;

	i = 0;
	while (old_value[i])
	{
		if (is_to_expand(old_value[i]))
			word = handle_special_word(minishell, old_value, &i, is_quoted);
		else
			word = handle_normal_word(old_value, &i);
		if (!word)
		{
			free(*new_value);
			return (ERR_MALLOC);
		}
		*new_value = create_new_value(*new_value, word);
		if (!*new_value)
			return (ERR_MALLOC);
	}
	return (SUCCESS);
}
