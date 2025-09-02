/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_re.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:23:07 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/02 14:23:11 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(t_list *tok_lst, t_list *head, t_status status, t_cmd *cmd)
{
	t_token	*tok;

	tok = tok_lst->content;
	free_cmd(cmd);
	if (status == ERR_SYSTEM)
		assert_error_parser(head, "malloc", ERR_SYSTEM);
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
	}
}

t_status	add_newlst(t_list **head, void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
		return (ERR_SYSTEM);
	ft_lstadd_back(head, new);
	return (SUCCESS);
}

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
	t_token		*tok;
	t_redir		*redir;
	t_status	status;

	// printf("get_redirection\n");
	tok = (*tok_lst)->content;
	redir = ft_calloc(sizeof(t_redir), 1);
	if (!redir)
		return (ERR_SYSTEM);
	handle_redir_type(tok, redir);
	if (!(*tok_lst)->next)
	{
		free(redir);
		return (ERR_SYNTAX);
	}
	*tok_lst = (*tok_lst)->next;
	tok = (*tok_lst)->content;
	status = handle_redir_value(tok, redir);
	if (status != SUCCESS)
		return (status);
	status = add_newlst(&(cmd->redir_lst), (void *)redir);
	if (status != SUCCESS)
		return (status);
	*tok_lst = (*tok_lst)->next;
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
t_status	handle_args_and_redir(t_list **tok_lst, t_cmd *cmd)
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
	args = ft_calloc(sizeof(char *) * (n + 1), 1);
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

t_status	handle_pipe(t_list **tok_lst)
{
	// t_token	*tok;
	if (!(*tok_lst)->next)
		return (ERR_SYNTAX);
	*tok_lst = (*tok_lst)->next;
	// tok = (*tok_lst)->content;
	// if (tok->type == TK_PIPE)
	// 	return (ERR_SYNTAX);
	return (SUCCESS);
}

t_status	get_cmd(t_list **tok_lst, t_cmd *cmd)
{
	t_status	status;

	// t_token		*tok;
	// while (*tok_lst)
	// {
	// tok = (*tok_lst)->content;
	// if (tok->type != TK_PIPE)
	status = handle_args_and_redir(tok_lst, cmd);
	if (status != SUCCESS)
		return (status);
	// else
	// {
	if (*tok_lst)
		status = handle_pipe(tok_lst);
	// break ;
	// }
	// if (status != SUCCESS)
	// 	return (status);
	// }
	return (status);
}

t_list	*get_cmd_lst(t_list *tok_lst)
{
	t_cmd		*cmd;
	t_status	status;
	t_list		*head;

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
		if (status != SUCCESS)
		{
			handle_error(tok_lst, head, status, cmd);
			return (NULL);
		}
		status = add_newlst(&head, (void *)cmd);
		if (status == ERR_SYSTEM)
		{
			free_cmd(cmd);
			assert_error_parser(head, "malloc", ERR_SYSTEM);
			return (NULL);
		}
	}
	return (head);
}

int	count_cmds(t_list *cmd_lst)
{
	int	n;

	n = 0;
	while (cmd_lst)
	{
		n++;
		cmd_lst = cmd_lst->next;
	}
	return (n);
}

t_pipeline	*parse(t_list *tok_lst)
{
	t_pipeline	*pipeline;

	pipeline = ft_calloc(sizeof(t_pipeline), 1);
	if (!pipeline)
	{
		assert_error_parser(NULL, "malloc", ERR_SYSTEM);
		return (NULL);
	}
	pipeline->cmd_lst = get_cmd_lst(tok_lst);
	if (!pipeline->cmd_lst)
	{
		free(pipeline);
		return (NULL);
	}
	pipeline->n = count_cmds(pipeline->cmd_lst);
	return (pipeline);
}
