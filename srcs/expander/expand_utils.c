/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:31:17 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/26 23:04:23 by aomatsud         ###   ########.fr       */
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

int	is_valid_key_first_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	else
		return (0);
}

int	is_valid_key_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	else
		return (0);
}
