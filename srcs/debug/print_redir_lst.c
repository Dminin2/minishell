/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_redir_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:48:08 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/11 15:37:56 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redir_lst(t_list *head, int fd)
{
	t_redir	*redir;
	int		i;

	dprintf(fd, "  Rdirections:\n");
	i = 1;
	while (head)
	{
		redir = head->content;
		dprintf(fd, "    [%d]\n", i);
		dprintf(fd, "      value : %s\n", redir->value);
		if (redir->type == R_IN)
			dprintf(fd, "      type  : R_IN\n");
		else if (redir->type == R_OUT)
			dprintf(fd, "      type  : R_OUT\n");
		else if (redir->type == R_HEREDOC)
			dprintf(fd, "      type  : R_HEREDOC\n");
		else if (redir->type == R_APPEND)
			dprintf(fd, "      type  : R_APPEND\n");
		else
			dprintf(fd, "      type  : null\n");
		head = head->next;
		i++;
	}
}
