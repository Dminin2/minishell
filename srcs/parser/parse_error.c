/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:23:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/07 10:57:02 by aomatsud         ###   ########.fr       */
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

void	handle_syntax_error(t_minishell *minishell, t_list *tok_lst,
		t_list **head)
{
	t_token	*tok;

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
		minishell->should_exit = 1;
}

void	*handle_error(t_minishell *minishell, t_list *tok_lst, t_list **head,
		t_status status)
{
	if (status == ERR_MALLOC)
		error_cmd_ir_lst(minishell, head, "malloc", ERR_MALLOC);
	else if (status == ERR_SYNTAX)
		handle_syntax_error(minishell, tok_lst, head);
	else if (status == ERR_HD_FILE)
		error_cmd_ir_lst(minishell, head, TMP_FD_ERR, ERR_HD_FILE);
	else if (status == RCV_SIGINT)
	{
		ft_lstclear(head, free_cmd_ir_wrapper);
		minishell->last_status = 130;
		g_sig = 0;
	}
	return (NULL);
}
