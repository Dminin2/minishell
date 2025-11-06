/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_redir_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:48:08 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/16 01:51:53 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redir_lst(t_list *head, int fd)
{
	t_redir	*redir;
	int		i;

	ft_dprintf_buf(fd, "  Rdirections:\n");
	i = 1;
	while (head)
	{
		redir = head->content;
		ft_dprintf_buf(fd, "    [%d]\n", i);
		ft_dprintf_buf(fd, "      value : %s\n", redir->value);
		if (redir->type == R_IN)
			ft_dprintf_buf(fd, "      type  : R_IN\n");
		else if (redir->type == R_OUT)
			ft_dprintf_buf(fd, "      type  : R_OUT\n");
		else if (redir->type == R_HEREDOC)
			ft_dprintf_buf(fd, "      type  : R_HEREDOC\n");
		else if (redir->type == R_APPEND)
			ft_dprintf_buf(fd, "      type  : R_APPEND\n");
		else
			ft_dprintf_buf(fd, "      type  : null\n");
		head = head->next;
		i++;
	}
}
