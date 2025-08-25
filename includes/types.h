/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:21:17 by aomatsud          #+#    #+#             */
/*   Updated: 2025/08/25 19:39:02 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "libft.h"

typedef struct s_cmd
{
	char		*path;
	char		**args;
}				t_cmd;

typedef enum e_tok_types
{
	TK_WORD,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_HEREDOC,
	TK_APPEND,
	TK_EOF
}				t_tok_types;

typedef struct s_token
{
	t_tok_types	type;
	char		*value;
}				t_token;

typedef struct s_lexer
{
	const char	*line;
	int			pos;
}				t_lexer;

typedef enum e_status
{
	SUCCESS,
	ERR_SYSTEM,
	ERR_SYNTAX,
	ERR_CMD_NOT_FOUND,
	ERR_NOT_VALID_PATH
}				t_status;

#endif
