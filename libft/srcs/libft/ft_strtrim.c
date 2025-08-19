/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:30:10 by aomatsud          #+#    #+#             */
/*   Updated: 2025/05/01 15:41:23 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*no_set(void)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * 1);
	if (!res)
		return (NULL);
	res[0] = '\0';
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		i;
	char	*res;

	i = 0;
	while (s1[i] && check(s1[i], set))
		i++;
	if (!s1[i])
		return (no_set());
	start = i;
	while (s1[i])
		i++;
	i--;
	while (i >= start && check(s1[i], set))
		i--;
	res = (char *)malloc(sizeof(char) * (i - start + 2));
	if (!res)
		return (NULL);
	ft_strlcpy(res, &s1[start], i - start + 2);
	return (res);
}
