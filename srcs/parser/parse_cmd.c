/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_ir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:22:44 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/05 13:12:54 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	get_cmd_ir_args(t_list **tok_lst, t_cmd_ir *cmd_ir)
{
	t_token		*tok;
	char		*args;
	t_status	status;

	tok = (*tok_lst)->content;
	args = ft_strdup(tok->value);
	if (!args)
		return (ERR_MALLOC);
	status = add_newlst(&(cmd_ir->args_lst), args);
	if (status != SUCCESS)
	{
		free(args);
		return (status);
	}
	*tok_lst = (*tok_lst)->next;
	return (SUCCESS);
}

t_status	get_simple_command(t_list **tok_lst, t_cmd_ir *cmd_ir)
{
	t_token		*tok;
	t_status	status;

	tok = (*tok_lst)->content;
	if (tok->type == TK_PIPE)
		return (ERR_SYNTAX);
	while (*tok_lst)
	{
		tok = (*tok_lst)->content;
		if (tok->type == TK_PIPE)
			break ;
		else if (tok->type == TK_WORD)
			status = get_cmd_ir_args(tok_lst, cmd_ir);
		else
			status = get_redirection(tok_lst, cmd_ir);
		if (status != SUCCESS)
			return (status);
	}
	return (SUCCESS);
}
