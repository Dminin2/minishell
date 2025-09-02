/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:57:36 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/02 20:57:43 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_list *head)
{
	t_token *tok;

	while (head)
	{
		tok = head->content;
		if (tok->type == TK_WORD)
			printf("%s\n", tok->value);
		else if (tok->type == TK_PIPE)
			printf("|\n");
		else if (tok->type == TK_REDIR_IN)
			printf("<\n");
		else if (tok->type == TK_REDIR_OUT)
			printf(">\n");
		else if (tok->type == TK_HEREDOC)
			printf("<<\n");
		else if (tok->type == TK_APPEND)
			printf(">>\n");
		head = head->next;
	}
}
