/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:19:42 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/02 18:19:43 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	consume_blank(t_lexer *lex)
{
	while (lex->line[lex->pos] && is_blank(lex->line[lex->pos]))
		lex->pos++;
}

int	is_metacharacter(char c)
{
	if (ft_strchr("|<>", c))
		return (1);
	else
		return (0);
}

t_status	consume_quote(t_lexer *lex, char quote_char)
{
	lex->pos++;
	while (lex->line[lex->pos] && lex->line[lex->pos] != quote_char)
		lex->pos++;
	if (!lex->line[lex->pos])
		return (ERR_QUOTE);
	lex->pos++;
	return (SUCCESS);
}

int	scan_operator(t_lexer *lex, t_tok_types *op_type)
{
	if (lex->line[lex->pos + 1] && ft_strncmp(&(lex->line[lex->pos]), "<<",
			2) == 0)
		*op_type = TK_HEREDOC;
	else if (lex->line[lex->pos + 1] && ft_strncmp(&(lex->line[lex->pos]), ">>",
			2) == 0)
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
