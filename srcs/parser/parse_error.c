/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:23:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/02 22:55:01 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(t_list *tok_lst, t_list *head, t_status status)
{
	t_token	*tok;
	char	*token_str;

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
					token_str = "<";
				else if (tok->type == TK_REDIR_OUT)
					token_str = ">";
				else if (tok->type == TK_HEREDOC)
					token_str = "<<";
				else if (tok->type == TK_APPEND)
					token_str = ">>";
				else
					token_str = "|";
				assert_error_lst(head, token_str, ERR_SYNTAX,
					free_cmd_ir_wrapper);
			}
		}
		else
			assert_error_lst(head, "newline", ERR_SYNTAX, free_cmd_ir_wrapper);
	}
}
