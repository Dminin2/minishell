/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:23:12 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/15 23:19:41 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir_type(t_token *tok, t_redir *redir)
{
	if (tok->type == TK_REDIR_IN)
		redir->type = R_IN;
	else if (tok->type == TK_REDIR_OUT)
		redir->type = R_OUT;
	else if (tok->type == TK_HEREDOC)
		redir->type = R_HEREDOC;
	else if (tok->type == TK_APPEND)
		redir->type = R_APPEND;
}

t_status	handle_redir_value(t_token *tok, t_redir *redir)
{
	if (tok->type != TK_WORD)
		return (ERR_SYNTAX);
	redir->value = ft_strdup(tok->value);
	if (!redir->value)
		return (ERR_MALLOC);
	return (SUCCESS);
}

t_status	get_redirection(t_list **tok_lst, t_cmd_ir *cmd_ir)
{
	t_redir		*redir;
	t_status	status;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (ERR_MALLOC);
	redir->fd_hd = -1;
	handle_redir_type((*tok_lst)->content, redir);
	*tok_lst = (*tok_lst)->next;
	if (!*tok_lst)
	{
		free(redir);
		return (ERR_SYNTAX);
	}
	status = handle_redir_value((*tok_lst)->content, redir);
	if (status != SUCCESS)
	{
		free(redir);
		return (status);
	}
	status = add_newlst(&(cmd_ir->redir_lst), (void *)redir);
	if (status != SUCCESS)
	{
		free_redir(redir);
		return (status);
	}
	*tok_lst = (*tok_lst)->next;
	return (SUCCESS);
}
