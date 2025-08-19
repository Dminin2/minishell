/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:13:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/05/01 15:40:56 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;
	int	in_word;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		in_word = 0;
		while (s[i] && s[i] != c)
		{
			if (in_word == 0)
			{
				in_word = 1;
				count++;
			}
			i++;
		}
	}
	return (count);
}

static char	**free_words(char **str, int i)
{
	while (i)
	{
		i--;
		free(str[i]);
	}
	free(str);
	return (NULL);
}

static char	*put_words(char const *s, char c)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	res = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			res[j] = put_words(&s[i], c);
			if (!res[j])
				return (free_words(res, j));
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	res[j] = NULL;
	return (res);
}
