/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:31:17 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/04 11:33:43 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_both(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
	{
		free_both(s1, s2);
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
	free_both(s1, s2);
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
