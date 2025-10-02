/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:23:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/02 22:38:46 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(t_list *tok_lst, t_list *head, t_status status)
{
	t_token	*tok;
	char	*tk;

	if (status == ERR_SYSTEM)
		assert_error_lst(head, "malloc", ERR_SYSTEM, free_cmd_ir_wrapper);
	else if (status == ERR_SYNTAX)
	{
		if (tok_lst)
		{
			tok = tok_lst->content;
			if (tok->value)
				assert_error_lst(head, tok->value, ERR_SYNTAX,
					free_cmd_ir_wrapper);
			else
			{
				if (tok->type == TK_REDIR_IN)
					tk = "<";
				else if (tok->type == TK_REDIR_OUT)
					tk = ">";
				else if (tok->type == TK_HEREDOC)
					tk = "<<";
				else if (tok->type == TK_APPEND)
					tk = ">>";
				else
					tk = "|";
				assert_error_lst(head, tk, ERR_SYNTAX, free_cmd_ir_wrapper);
			}
		}
		else
			assert_error_lst(head, "newline", ERR_SYNTAX, free_cmd_ir_wrapper);
	}
}
