/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:11:52 by aomatsud          #+#    #+#             */
/*   Updated: 2025/04/28 16:01:41 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	int		i;

	last = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			last = &((char *)s)[i];
		i++;
	}
	if (!(char)c)
		return (&((char *)s)[i]);
	return (last);
}
