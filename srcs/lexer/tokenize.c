/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:32:59 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/28 12:51:21 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	consume_blank(t_lexer *lex)
{
	while (lex->line[lex->pos] && isspace(lex->line[lex->pos]))
		lex->pos++;
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

// 特別処理をするmetacharacterであるかどうか確認する。
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
		return (ERR_SYSTEM);
	tok->type = *op_type;
	if (op_type == TK_HEREDOC || op_type == TK_APPEND)
		lex->pos += 2;
	else
		lex->pos += 1;
	new = ft_lstnew(tok);
	if (!new)
	{
		free(tok);
		return (ERR_SYSTEM);
	}
	ft_lstadd_back(head, new);
	return (SUCCESS);
}

t_status	handle_word(t_lexer *lex, t_list **head)
{
	t_token	*tok;
	t_list	*new;
	int		start;

	// 文字列の複製を作りたいので、startの位置を記録しておく
	start = lex->pos;
	// spaceにあたるまで繰り返す
	while (lex->line[lex->pos] && !isspace(lex->line[lex->pos]))
	{
		// single quoteの中はmetacharacterがきてもdouble quoteがきても読み飛ばす
		if (lex->line[lex->pos] == '\'')
		{
			lex->pos++;
			while (lex->line[lex->pos] && lex->line[lex->pos] != '\'')
				lex->pos++;
			// single quoteが見える前に終端にきたらエラー
			if (!lex->line[lex->pos])
				return (ERR_SYNTAX);
		}
		// double quoteも同じことをやる
		else if (lex->line[lex->pos] == '\"')
		{
			lex->pos++;
			while (lex->line[lex->pos] && lex->line[lex->pos] != '\"')
				lex->pos++;
			if (!lex->line[lex->pos])
				return (ERR_SYNTAX);
		}
		// metacharacterは特別扱いなので、そこで文字列が切れる
		else if (is_metacharacter(lex->line[lex->pos]))
			break ;
		lex->pos++;
	}
	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (ERR_SYSTEM);
	tok->type = TK_WORD;
	// lex->line[start]からlex->line[lex->pos]までを複製する
	tok->value = ft_substr(lex->line, start, lex->pos - start);
	if (!tok->value)
	{
		free(tok);
		return (ERR_SYSTEM);
	}
	// tokを内蔵した新しいt_listをつくる
	new = ft_lstnew(tok);
	if (!new)
	{
		free_token(tok);
		return (ERR_SYSTEM);
	}
	// new listを連結する
	ft_lstadd_back(head, new);
	return (SUCCESS);
}

t_list	*tokenize(char *line)
{
	t_list		*head;
	t_lexer		lex;
	t_status	status;
	t_tok_types	op_type;

	// ft_lst系を使いたかったのでlst使ってるけど、malloc倍に増えるからなくてもよし
	head = NULL;
	// lexはreadlineで読み込んだlineを保存するのと、どこまで読んだかposに保存しておくやつ
	lex.line = line;
	lex.pos = 0;
	// malloc失敗ならERR_SYSTEM,quoteが閉じていないならERR_SYNTAXで返ってくる
	status = SUCCESS;
	// 文字列終端まで読み込む
	while (lex.line[lex.pos])
	{
		// spaceならそれをスッキプする
		if (isspace(lex.line[lex.pos]))
			consume_blank(&lex);
		// operator(pipe,redirection)ならその情報をlstに繋げる
		else if (scan_operator(&lex, &op_type))
			status = handle_operator(&lex, &head, &op_type);
		// それ以外ならwordとしてそのまま読み込みlstに繋げる
		else
			status = handle_word(&lex, &head);
		// statusを確認してエラーがあったらエラーメッセージを表示させ、その時点でmainのループに戻る
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
