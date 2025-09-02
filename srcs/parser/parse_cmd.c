/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:22:44 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/02 21:54:18 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_list *tok_lst)
{
	int		n;
	t_token	*tok;

	n = 0;
	while (tok_lst)
	{
		tok = tok_lst->content;
		if (tok->type == TK_PIPE)
			break ;
		else if (tok->type == TK_WORD)
			n++;
		tok_lst = tok_lst->next;
	}
	return (n);
}

t_status	get_cmd_args(t_list **tok_lst, char **args, int *pos)
{
	t_token	*tok;

	tok = (*tok_lst)->content;
	args[*pos] = ft_strdup(tok->value);
	if (!args[*pos])
	{
		free_args(args);
		return (ERR_SYSTEM);
	}
	(*pos)++;
	*tok_lst = (*tok_lst)->next;
	return (SUCCESS);
}

t_status	get_simple_command(t_list **tok_lst, t_cmd *cmd)
{
	t_token		*tok;
	char		**args;
	int			n;
	int			i;
	t_status	status;

	tok = (*tok_lst)->content;
	if (tok->type == TK_PIPE)
		return (ERR_SYNTAX);
	n = count_args(*tok_lst);
	args = ft_calloc(n + 1, sizeof(char *));
	if (!args)
		return (ERR_SYSTEM);
	i = 0;
	while (*tok_lst)
	{
		tok = (*tok_lst)->content;
		if (tok->type == TK_PIPE)
			break ;
		else if (tok->type == TK_WORD)
			status = get_cmd_args(tok_lst, args, &i);
		else
			status = get_redirection(tok_lst, cmd);
		if (status != SUCCESS)
		{
			free_args(args);
			return (status);
		}
	}
	cmd->args = args;
	return (SUCCESS);
}
