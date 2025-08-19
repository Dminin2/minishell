/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:29:46 by aomatsud          #+#    #+#             */
/*   Updated: 2025/05/01 15:53:43 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*result;
	size_t			total_len;
	size_t			i;

	i = 0;
	if (!nmemb || !size)
	{
		result = malloc(1);
		if (!result)
			return (NULL);
		return (result);
	}
	if (size > 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	total_len = nmemb * size;
	result = malloc(total_len);
	if (!result)
		return (NULL);
	while (i < total_len)
	{
		result[i] = 0;
		i++;
	}
	return ((void *)result);
}
