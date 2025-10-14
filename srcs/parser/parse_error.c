/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:23:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/13 15:18:54 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(t_minishell *minishell, t_list *tok_lst, t_list *head, t_status status)
{
	t_token	*tok;
	char	*token_str;

	if (status == ERR_SYSTEM)
		minishell->last_status = assert_error_lst(head, "malloc", ERR_SYSTEM, free_cmd_ir_wrapper);
	else if (status == ERR_SYNTAX)
	{
		if (tok_lst)
		{
			tok = tok_lst->content;
			if (tok->value)
				minishell->last_status = assert_error_lst(head, tok->value, ERR_SYNTAX,
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
				minishell->last_status = assert_error_lst(head, token_str, ERR_SYNTAX,
					free_cmd_ir_wrapper);
			}
		}
		else
			minishell->last_status = assert_error_lst(head, "newline", ERR_SYNTAX, free_cmd_ir_wrapper);
	}
}
