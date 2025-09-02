/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:23:12 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/02 17:47:56 by aomatsud         ###   ########.fr       */
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
	{
		free(redir);
		return (ERR_SYNTAX);
	}
	redir->value = ft_strdup(tok->value);
	if (!redir->value)
	{
		free(redir);
		return (ERR_SYSTEM);
	}
	return (SUCCESS);
}

t_status	get_redirection(t_list **tok_lst, t_cmd *cmd)
{
	t_redir		*redir;
	t_status	status;

	redir = ft_calloc(sizeof(t_redir), 1);
	if (!redir)
		return (ERR_SYSTEM);
	handle_redir_type((*tok_lst)->content, redir);
	if (!(*tok_lst)->next)
	{
		free(redir);
		return (ERR_SYNTAX);
	}
	*tok_lst = (*tok_lst)->next;
	status = handle_redir_value((*tok_lst)->content, redir);
	if (status != SUCCESS)
		return (status);
	status = add_newlst(&(cmd->redir_lst), (void *)redir);
	if (status != SUCCESS)
	{
		free(redir);
		return (status);
	}
	*tok_lst = (*tok_lst)->next;
	return (SUCCESS);
}
