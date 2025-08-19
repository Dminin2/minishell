/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:48:47 by aomatsud          #+#    #+#             */
/*   Updated: 2025/04/28 16:02:18 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	int		pos;

	i = 0;
	if (!little[0])
		return ((char *)big);
	while (big[i] && i < len)
	{
		pos = i;
		j = 0;
		while (little[j] && big[i + j] == little[j] && i + j < len)
			j++;
		if (!little[j])
			return (&((char *)big)[pos]);
		i++;
	}
	return (NULL);
}
