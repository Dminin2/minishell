/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:21:35 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/18 16:07:38 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include <stdlib.h>

typedef struct s_input	t_input;

typedef enum e_tok_types
{
	TK_WORD,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_HEREDOC,
	TK_APPEND,
	TK_EOF
}						t_tok_types;

typedef struct s_token
{
	t_tok_types			type;
	char				*value;
}						t_token;

typedef struct s_lexer
{
	const char			*line;
	int					pos;
}						t_lexer;

t_list					*tokenize(t_minishell *minishell, t_input *input);

void					free_token_wrapper(void *tok);
void					free_token(t_token *tok);

void					consume_blank(t_lexer *lex);
int						is_metacharacter(char c);
t_status				consume_quote(t_lexer *lex, char quote_char);
int						scan_operator(t_lexer *lex, t_tok_types *op_type);

#endif
