/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 01:50:00 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/31 15:05:10 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir_wrapper(void *redir)
{
	free_redir((t_redir *)redir);
}

void	free_redir(t_redir *redir)
{
	if (redir)
	{
		if (redir->value)
			free(redir->value);
		if (redir->fd_hd >= 0)
			close(redir->fd_hd);
		free(redir);
	}
}
