/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:23:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/25 13:20:44 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error(t_list *tok_lst, t_list *head, t_status status)
{
	t_token	*tok;
	char	*token_str;

	if (status == ERR_MALLOC)
		return (error_lst(head, "malloc", ERR_MALLOC, free_cmd_ir_wrapper));
	else
	{
		if (tok_lst)
		{
			tok = tok_lst->content;
			if (tok->value)
				return (error_lst(head, tok->value, ERR_SYNTAX,
						free_cmd_ir_wrapper));
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
				return (error_lst(head, token_str, ERR_SYNTAX,
						free_cmd_ir_wrapper));
			}
		}
		else
			return (error_lst(head, "newline", ERR_SYNTAX,
					free_cmd_ir_wrapper));
	}
}
