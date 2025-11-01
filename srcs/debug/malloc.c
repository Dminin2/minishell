/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:29:09 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/01 17:18:04 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MALLOC_FAILED 50

void	*my_calloc(size_t nmemb, size_t size)
{
	unsigned char	*result;
	size_t			total_len;
	size_t			i;
	static int		malloc_num = 0;

	if (malloc_num == MALLOC_FAILED)
	{
		dprintf(STDERR_FILENO, "my_calloc: faild\n");
		malloc_num = 0;
		return (NULL);
	}
	malloc_num++;
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
