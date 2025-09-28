/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:32:59 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/28 14:19:33 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	consume_blank(t_lexer *lex)
{
	while (lex->line[lex->pos] && isspace(lex->line[lex->pos]))
		lex->pos++;
}

t_status	consume_quote(t_lexer *lex, char quote_char)
{
	lex->pos++;
	while (lex->line[lex->pos] && lex->line[lex->pos] != quote_char)
		lex->pos++;
	if (!lex->line[lex->pos])
		return (ERR_SYNTAX);
	return (SUCCESS);
}

int	scan_operator(t_lexer *lex, t_tok_types *op_type)
{
	if (ft_strncmp(&(lex->line[lex->pos]), "<<", 2) == 0)
		*op_type = TK_HEREDOC;
	else if (ft_strncmp(&(lex->line[lex->pos]), ">>", 2) == 0)
		*op_type = TK_APPEND;
	else if (lex->line[lex->pos] == '<')
		*op_type = TK_REDIR_IN;
	else if (lex->line[lex->pos] == '>')
		*op_type = TK_REDIR_OUT;
	else if (lex->line[lex->pos] == '|')
		*op_type = TK_PIPE;
	else
		return (0);
	return (1);
}

int	is_metacharacter(char c)
{
	if (ft_strchr("|<>", c))
		return (1);
	else
		return (0);
}

t_status	handle_operator(t_lexer *lex, t_list **head, t_tok_types *op_type)
{
	t_token	*tok;
	t_list	*new;

	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (ERR_MALLOC);
	tok->type = *op_type;
	if (tok->type == TK_HEREDOC || tok->type == TK_APPEND)
		lex->pos += 2;
	else
		lex->pos += 1;
	new = ft_lstnew(tok);
	if (!new)
	{
		free(tok);
		return (ERR_MALLOC);
	}
	ft_lstadd_back(head, new);
	return (SUCCESS);
}

t_status	handle_word(t_lexer *lex, t_list **head)
{
	t_token		*tok;
	t_list		*new;
	int			start;
	t_status	status;

	start = lex->pos;
	status = SUCCESS;
	while (lex->line[lex->pos] && !isspace(lex->line[lex->pos]))
	{
		if (lex->line[lex->pos] == '\'' || lex->line[lex->pos] == '\"')
		{
			status = consume_quote(lex, lex->line[lex->pos]);
			if (status == ERR_SYNTAX)
				return (ERR_SYNTAX);
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
	new = ft_lstnew(tok);
	if (!new)
	{
		free_token(tok);
		return (ERR_MALLOC);
	}
	ft_lstadd_back(head, new);
	return (SUCCESS);
}

t_list	*tokenize(char *line)
{
	t_list		*head;
	t_lexer		lex;
	t_status	status;
	t_tok_types	op_type;

	head = NULL;
	lex.line = line;
	lex.pos = 0;
	status = SUCCESS;
	while (lex.line[lex.pos])
	{
		if (isspace(lex.line[lex.pos]))
			consume_blank(&lex);
		else if (scan_operator(&lex, &op_type))
			status = handle_operator(&lex, &head, &op_type);
		else
			status = handle_word(&lex, &head);
		if (status != SUCCESS)
		{
			if (status == ERR_MALLOC)
				assert_error(head, "malloc", ERR_MALLOC);
			else if (status == ERR_SYNTAX)
				assert_error(head, "Unclosed quote", ERR_SYNTAX);
			return (NULL);
		}
	}
	return (head);
}
