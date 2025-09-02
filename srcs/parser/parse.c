/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:40:51 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/02 00:16:26 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	get_redirection(t_list **tok_lst, t_cmd *cmd)
{
	t_token	*tok;
	t_redir	*redir;
	t_list	*head;
	t_list	*new;

	head = cmd->redir_lst;
	while (*tok_lst)
	{
		tok = (*tok_lst)->content;
		if (tok->type == TK_PIPE || tok->type == TK_WORD)
			break ;
		redir = ft_calloc(sizeof(t_redir), 1);
		if (!redir)
			return (ERR_SYSTEM);
		if (tok->type == TK_REDIR_IN)
			redir->type = R_IN;
		else if (tok->type == TK_REDIR_OUT)
			redir->type = R_OUT;
		else if (tok->type == TK_HEREDOC)
			redir->type = R_HEREDOC;
		else if (tok->type == TK_APPEND)
			redir->type = R_APPEND;
		if (!(*tok_lst)->next)
		{
			free(redir);
			return (ERR_SYNTAX);
		}
		*tok_lst = (*tok_lst)->next;
		tok = (*tok_lst)->content;
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
		new = ft_lstnew(redir);
		if (!new)
		{
			free_redir(redir);
			return (ERR_SYSTEM);
		}
		ft_lstadd_back(&head, new);
		*tok_lst = (*tok_lst)->next;
	}
	cmd->redir_lst = head;
	return (SUCCESS);
}

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

t_status	get_cmd_args(t_list **tok_lst, t_cmd *cmd)
{
	t_token		*tok;
	char		**args;
	int			n;
	int			i;
	t_status	status;

	n = count_args(*tok_lst);
	args = ft_calloc(sizeof(char *) * (n + 1), 1);
	if (!args)
		return (ERR_SYSTEM);
	i = 0;
	while (*tok_lst && i < n)
	{
		tok = (*tok_lst)->content;
		if (tok->type == TK_PIPE)
			break ;
		else if (tok->type == TK_WORD)
		{
			args[i] = ft_strdup(tok->value);
			if (!args[i])
			{
				free_args(args);
				return (ERR_SYSTEM);
			}
			i++;
			*tok_lst = (*tok_lst)->next;
		}
		else
		{
			status = get_redirection(tok_lst, cmd);
			if (status != SUCCESS)
				return (status);
		}
	}
	cmd->args = args;
	return (SUCCESS);
}

t_status	get_cmd(t_list **tok_lst, t_cmd *cmd)
{
	t_status	status;
	t_token		*tok;

	while (*tok_lst)
	{
		tok = (*tok_lst)->content;
		if (tok->type == TK_WORD)
			status = get_cmd_args(tok_lst, cmd);
		else if (tok->type != TK_PIPE)
			status = get_redirection(tok_lst, cmd);
		else
		{
			if (!(*tok_lst)->next)
				return (ERR_SYNTAX);
			*tok_lst = (*tok_lst)->next;
			tok = (*tok_lst)->content;
			if (tok->type == TK_PIPE)
				return (ERR_SYNTAX);
			break ;
		}
		if (status != SUCCESS)
			return (status);
	}
	return (SUCCESS);
}

t_pipeline	*parse(t_list *tok_lst)
{
	t_token		*tok;
	t_cmd		*cmd;
	t_status	status;
	t_list		*head;
	int			n;
	t_pipeline	*pipeline;
	t_list		*new;

	n = 0;
	head = NULL;
	while (tok_lst)
	{
		cmd = ft_calloc(sizeof(t_cmd), 1);
		if (!cmd)
		{
			assert_error_parser(head, "malloc", ERR_SYSTEM);
			return (NULL);
		}
		status = get_cmd(&tok_lst, cmd);
		if (status == ERR_SYSTEM)
		{
			assert_error_parser(head, "malloc", ERR_SYSTEM);
			free_cmd(cmd);
			return (NULL);
		}
		else if (status == ERR_SYNTAX)
		{
			tok = tok_lst->content;
			if (tok->value)
				assert_error_parser(head, tok->value, ERR_SYNTAX);
			else
			{
				if (tok->type == TK_REDIR_IN)
					assert_error_parser(head, "<", ERR_SYNTAX);
				else if (tok->type == TK_REDIR_OUT)
					assert_error_parser(head, ">", ERR_SYNTAX);
				else if (tok->type == TK_HEREDOC)
					assert_error_parser(head, "<<", ERR_SYNTAX);
				else if (tok->type == TK_APPEND)
					assert_error_parser(head, ">>", ERR_SYNTAX);
				else
					assert_error_parser(head, "|", ERR_SYNTAX);
			}
			free_cmd(cmd);
			return (NULL);
		}
		new = ft_lstnew(cmd);
		if (!new)
		{
			assert_error_parser(head, "malloc", ERR_SYSTEM);
			free_cmd(cmd);
			return (NULL);
		}
		ft_lstadd_back(&head, new);
		n++;
	}
	pipeline = ft_calloc(sizeof(t_pipeline), 1);
	if (!pipeline)
	{
		assert_error_parser(head, "malloc", ERR_SYSTEM);
		return (NULL);
	}
	pipeline->cmd_lst = head;
	pipeline->n = n;
	return (pipeline);
}
