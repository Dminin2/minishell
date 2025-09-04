/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:21:17 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/04 20:07:51 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "libft.h"

typedef enum e_status
{
	SUCCESS,
	FAILURE,
	ERR_SYSTEM,
	ERR_SYNTAX,
	ERR_CMD_NOT_FOUND,
	ERR_NOT_VALID_PATH,
	ERR_FILE,
	ERR_DUP,
	ERR_MALLOC
}					t_status;

typedef enum e_tok_types
{
	TK_WORD,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_HEREDOC,
	TK_APPEND,
	TK_EOF
}					t_tok_types;

typedef struct s_token
{
	t_tok_types		type;
	char			*value;
}					t_token;

typedef struct s_lexer
{
	const char		*line;
	int				pos;
}					t_lexer;

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_HEREDOC,
	R_APPEND
}					t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*value;
	int				fd_hd;
}					t_redir;

typedef struct s_cmd
{
	char			**args;
	char			*path;
	t_list			*redir_lst;
}					t_cmd;

typedef struct s_pipeline
{
	t_list			*cmd_lst;
	int				n;
}					t_pipeline;

typedef struct s_redir_err
{
	t_status		status;
	t_redir			*redir_err;
}					t_redir_err;

#endif
