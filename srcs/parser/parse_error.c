/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:23:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/02 20:51:59 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(t_list *tok_lst, t_list *head, t_status status)
{
	t_token	*tok;

	if (status == ERR_SYSTEM)
		assert_error_parser(head, "malloc", ERR_SYSTEM);
	else if (status == ERR_SYNTAX)
	{
		if (tok_lst)
		{
			tok = tok_lst->content;
			if (tok->value)
				assert_error_parser(head, tok->value, ERR_SYNTAX);
			else
			{
				if (tok->type == TK_REDIR_IN)
					assert_error_parser(head, "<", ERR_SYNTAX);
				else if (tok->type == TK_REDIR_OUT)
					assert_error_parser(head, ">", ERR_SYNTAX);
				else if (tok->type == TK_HEREDOC)
					assert_error_parser(head, "<<", ERR_SYNTAX);
				else if (tok->type == TK_APPEND)
					assert_error_parser(head, ">>", ERR_SYNTAX);
				else
					assert_error_parser(head, "|", ERR_SYNTAX);
			}
		}
		else
			assert_error_parser(head, "newline", ERR_SYNTAX);
	}
}
