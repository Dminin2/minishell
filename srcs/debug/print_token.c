/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:57:36 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/16 01:52:12 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_list *head, int fd)
{
	t_token	*tok;

	ft_dprintf(fd, "===  token  ===\n");
	while (head)
	{
		tok = head->content;
		if (tok->type == TK_WORD)
			ft_dprintf(fd, "[WORD: %s]\n", tok->value);
		else if (tok->type == TK_PIPE)
			ft_dprintf(fd, "[PIPE: |]\n");
		else if (tok->type == TK_REDIR_IN)
			ft_dprintf(fd, "[R_IN: <]\n");
		else if (tok->type == TK_REDIR_OUT)
			ft_dprintf(fd, "[R_OUT: >]\n");
		else if (tok->type == TK_HEREDOC)
			ft_dprintf(fd, "[R_HD: <<]\n");
		else if (tok->type == TK_APPEND)
			ft_dprintf(fd, "[R_APP: >>]\n");
		head = head->next;
	}
	ft_dprintf(fd, "\n");
}
