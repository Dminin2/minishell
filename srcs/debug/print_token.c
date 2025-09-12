/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:57:36 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/12 00:13:49 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_list *head)
{
	t_token	*tok;

	printf("===  token  ===\n");
	while (head)
	{
		tok = head->content;
		if (tok->type == TK_WORD)
			printf("[WORD: %s]\n", tok->value);
		else if (tok->type == TK_PIPE)
			printf("[PIPPE: |]\n");
		else if (tok->type == TK_REDIR_IN)
			printf("[R_IN: <]\n");
		else if (tok->type == TK_REDIR_OUT)
			printf("[R_OUT: >]\n");
		else if (tok->type == TK_HEREDOC)
			printf("[R_HD: <<]\n");
		else if (tok->type == TK_APPEND)
			printf("[R_APP: >>]\n");
		head = head->next;
	}
	printf("\n");
}
