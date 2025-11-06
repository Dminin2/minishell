/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:23:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/06 10:43:57 by hmaruyam         ###   ########.fr       */
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

void	handle_error(t_minishell *minishell, t_list *tok_lst, t_list *head,
		t_status status)
{
	t_token	*tok;

	if (status == ERR_MALLOC)
		minishell->last_status = error_lst(head, "malloc", ERR_MALLOC,
				free_cmd_ir_wrapper);
	else if (status == ERR_SYNTAX)
	{
		if (tok_lst)
		{
			tok = tok_lst->content;
			if (tok->value)
				minishell->last_status = error_lst(head, tok->value, ERR_SYNTAX,
						free_cmd_ir_wrapper);
			else
			{
				minishell->last_status = error_lst(head,
						get_token_str(tok->type), ERR_SYNTAX,
						free_cmd_ir_wrapper);
			}
		}
		else
			minishell->last_status = error_lst(head, "newline", ERR_SYNTAX,
					free_cmd_ir_wrapper);
		if (!isatty(STDIN_FILENO))
			minishell->should_exit = 1;
	}
	else if (status == ERR_HD_FILE)
		minishell->last_status = error_lst(head, HD_FILE_ERR, status,
				free_cmd_ir_wrapper);
	else if (status == RCV_SIGINT)
	{
		ft_lstclear(&head, free_cmd_ir_wrapper);
		minishell->last_status = 130;
		g_sig = 0;
	}
}
