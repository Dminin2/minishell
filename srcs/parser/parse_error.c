/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:23:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/06 18:39:46 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_token_str(t_tok_types type)
{
	if (type == TK_REDIR_IN)
		return ("<");
	else if (type == TK_REDIR_OUT)
		return (">");
	else if (type == TK_HEREDOC)
		return ("<<");
	else if (type == TK_APPEND)
		return (">>");
	else
		return ("|");
}

void	handle_error(t_minishell *minishell, t_list *tok_lst, t_list **head,
		t_status status)
{
	t_token	*tok;

	if (status == ERR_MALLOC)
		error_cmd_ir_lst(minishell, head, "malloc", ERR_MALLOC);
	else if (status == ERR_SYNTAX)
	{
		if (tok_lst)
		{
			tok = tok_lst->content;
			if (tok->value)
				error_cmd_ir_lst(minishell, head, tok->value, ERR_SYNTAX);
			else
				error_cmd_ir_lst(minishell, head, get_token_str(tok->type),
					ERR_SYNTAX);
		}
		else
			error_cmd_ir_lst(minishell, head, "newline", ERR_SYNTAX);
		if (!isatty(STDIN_FILENO))
		{
			minishell->should_exit = 1;
			get_next_line(-1);
		}
	}
	else if (status == ERR_HD_FILE)
		error_cmd_ir_lst(minishell, head, HD_FILE_ERR, status);
	else if (status == RCV_SIGINT)
	{
		ft_lstclear(head, free_cmd_ir_wrapper);
		minishell->last_status = 130;
		g_sig = 0;
	}
}
