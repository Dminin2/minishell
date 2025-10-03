/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 20:04:37 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/03 20:05:11 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipes(int **pipes, int n)
{
	int i;

	i = 0;
	if (pipes)
	{
		while (i < n)
		{
			free(pipes[i]);
			i++;
		}
		free(pipes);
	}
}
