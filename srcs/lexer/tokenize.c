/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:32:59 by aomatsud          #+#    #+#             */
/*   Updated: 2025/08/25 20:32:00 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	consume_blank(t_lexer *lex)
{
	while (lex->line[lex->pos] && isspace(lex->line[lex->pos]))
		lex->pos++;
}

int	is_operator(t_lexer *lex)
{
	char	*op[] = {"|", "<<", ">>", "<", ">"};
	int		i;

	i = 0;
	while (i < 5)
	{
		if (!ft_memcmp(op[i], &(lex->line[lex->pos]), ft_strlen(op[i])))
			return (1);
		i++;
	}
	return (0);
}

int	is_metacharacter(char c)
{
	if (ft_strchr("|<>", c))
		return (1);
	else
		return (0);
}

t_status	handle_operator(t_lexer *lex, t_list **head)
{
	t_token	*tok;
	t_list	*new;

	tok = ft_calloc(sizeof(t_token), 1);
	if (!tok)
		return (ERR_SYSTEM);
	if (lex->line[lex->pos] == '<')
	{
		if (lex->line[++lex->pos] == '<')
			tok->type = TK_HEREDOC;
		else
			tok->type = TK_REDIR_IN;
	}
	else if (lex->line[lex->pos] == '>')
	{
		if (lex->line[++lex->pos] == '>')
			tok->type = TK_APPEND;
		else
			tok->type = TK_REDIR_OUT;
	}
	else
		tok->type = TK_PIPE;
	if (tok->type == TK_HEREDOC || tok->type == TK_APPEND
		|| tok->type == TK_PIPE)
		lex->pos++;
	new = ft_lstnew(tok);
	if (!new)
		return (ERR_SYSTEM);
	ft_lstadd_back(head, new);
	return (SUCCESS);
}

t_status	handle_word(t_lexer *lex, t_list **head)
{
	t_token	*tok;
	t_list	*new;
	int		start;

	start = lex->pos;
	tok = ft_calloc(sizeof(t_token), 1);
	if (!tok)
		return (ERR_SYSTEM);
	while (lex->line[lex->pos] && !isspace(lex->line[lex->pos]))
	{
		if (lex->line[lex->pos] == '\'')
		{
			lex->pos++;
			while (lex->line[lex->pos] && lex->line[lex->pos] != '\'')
				lex->pos++;
			if (!lex->line[lex->pos])
				return (ERR_SYNTAX);
		}
		else if (lex->line[lex->pos] == '\"')
		{
			lex->pos++;
			while (lex->line[lex->pos] && lex->line[lex->pos] != '\"')
				lex->pos++;
			if (!lex->line[lex->pos])
				return (ERR_SYNTAX);
		}
		else if (is_metacharacter(lex->line[lex->pos]))
			break ;
		lex->pos++;
	}
	tok->type = TK_WORD;
	tok->value = ft_substr(lex->line, start, lex->pos - start);
	if (!tok->value)
		return (ERR_SYSTEM);
	new = ft_lstnew(tok);
	if (!new)
		return (ERR_SYSTEM);
	ft_lstadd_back(head, new);
	return (SUCCESS);
}

t_list	*tokenize(char *line)
{
	t_list		*head;
	t_lexer		lex;
	t_status	status;

	head = NULL;
	lex.line = line;
	lex.pos = 0;
	status = SUCCESS;
	while (lex.line[lex.pos])
	{
		if (isspace(lex.line[lex.pos]))
			consume_blank(&lex);
		else if (is_operator(&lex))
			status = handle_operator(&lex, &head);
		else
			status = handle_word(&lex, &head);
		if (status != SUCCESS)
		{
			if (status == ERR_SYSTEM)
				assert_error(head, "malloc", ERR_SYSTEM);
			else
				assert_error(head, "Unclosed quote", ERR_SYNTAX);
			return (NULL);
		}
	}
	return (head);
}
