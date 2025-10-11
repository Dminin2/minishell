/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:57:36 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/11 19:09:45 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_list *head, int fd)
{
	t_token	*tok;

	dprintf(fd, "===  token  ===\n");
	while (head)
	{
		tok = head->content;
		if (tok->type == TK_WORD)
			dprintf(fd, "[WORD: %s]\n", tok->value);
		else if (tok->type == TK_PIPE)
			dprintf(fd, "[PIPE: |]\n");
		else if (tok->type == TK_REDIR_IN)
			dprintf(fd, "[R_IN: <]\n");
		else if (tok->type == TK_REDIR_OUT)
			dprintf(fd, "[R_OUT: >]\n");
		else if (tok->type == TK_HEREDOC)
			dprintf(fd, "[R_HD: <<]\n");
		else if (tok->type == TK_APPEND)
			dprintf(fd, "[R_APP: >>]\n");
		head = head->next;
	}
	dprintf(fd, "\n");
}
