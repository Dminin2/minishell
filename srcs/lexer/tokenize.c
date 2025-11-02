/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:32:59 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/28 00:17:56 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	handle_operator(t_lexer *lex, t_list **head, t_tok_types *op_type)
{
	t_token		*tok;
	t_status	status;

	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (ERR_MALLOC);
	tok->type = *op_type;
	if (tok->type == TK_HEREDOC || tok->type == TK_APPEND)
		lex->pos += 2;
	else
		lex->pos += 1;
	status = add_newlst(head, (void *)tok);
	if (status == ERR_MALLOC)
	{
		free_token(tok);
		return (ERR_MALLOC);
	}
	return (SUCCESS);
}

t_status	handle_word(t_lexer *lex, t_list **head)
{
	t_token		*tok;
	int			start;
	t_status	status;

	start = lex->pos;
	status = SUCCESS;
	while (lex->line[lex->pos] && !is_blank(lex->line[lex->pos]))
	{
		if (lex->line[lex->pos] == '\'' || lex->line[lex->pos] == '\"')
		{
			status = consume_quote(lex, lex->line[lex->pos]);
			if (status != SUCCESS)
				return (status);
			continue ;
		}
		else if (is_metacharacter(lex->line[lex->pos]))
			break ;
		lex->pos++;
	}
	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (ERR_MALLOC);
	tok->type = TK_WORD;
	tok->value = ft_substr(lex->line, start, lex->pos - start);
	if (!tok->value)
	{
		free(tok);
		return (ERR_MALLOC);
	}
	status = add_newlst(head, (void *)tok);
	if (status == ERR_MALLOC)
	{
		free_token(tok);
		return (ERR_MALLOC);
	}
	return (SUCCESS);
}

t_list	*tokenize(t_minishell *minishell, t_input *input)
{
	t_list		*head;
	t_lexer		lex;
	t_status	status;
	t_tok_types	op_type;

	head = NULL;
	lex.line = input->line;
	lex.pos = 0;
	status = SUCCESS;
	while (lex.line[lex.pos])
	{
		if (is_blank(lex.line[lex.pos]))
			consume_blank(&lex);
		else if (scan_operator(&lex, &op_type))
			status = handle_operator(&lex, &head, &op_type);
		else
			status = handle_word(&lex, &head);
		if (status != SUCCESS)
		{
			if (status == ERR_MALLOC)
				minishell->last_status = error_lst(head, "malloc", ERR_MALLOC,
						free_token_wrapper);
			else
			{
				if (input->is_eof)
					minishell->last_status = error_lst(head, "end of file",
							ERR_QUOTE, free_token_wrapper);
				else
					minishell->last_status = error_lst(head, "newline",
							ERR_QUOTE, free_token_wrapper);
			}
			return (NULL);
		}
	}
	return (head);
}
