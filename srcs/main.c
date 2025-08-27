/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:54:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/08/27 18:04:21 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_content(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!isspace(line[i]))
			return (1);
		i++;
	}
	return (0);
}

void	parse(t_cmd *cmd, char *line)
{
	if (!has_content(line))
		cmd->args = ft_split(line, 'A');
	else
		cmd->args = ft_split(line, ' ');
}

void	print_lst(t_list *head)
{
	t_token	*tok;

	while (head)
	{
		tok = head->content;
		if (tok->type == TK_WORD)
			printf("%s\n", tok->value);
		else if (tok->type == TK_PIPE)
			printf("|\n");
		else if (tok->type == TK_REDIR_IN)
			printf("<\n");
		else if (tok->type == TK_REDIR_OUT)
			printf(">\n");
		else if (tok->type == TK_HEREDOC)
			printf("<<\n");
		else if (tok->type == TK_APPEND)
			printf(">>\n");
		head = head->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	t_list	*lst;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = get_command_line();
		//入力終了
		if (!line)
			break ;
		lst = tokenize(line);
		if (!lst) // malloc失敗もしくはsytax error
		{
			free(line);
			continue ;
		}
		print_lst(lst);
		ft_lstclear(&lst, &free_token_wrapper);
		//コマンド実行できるように残しておいただけなのでまだ未完成のparse
		cmd = ft_calloc(sizeof(t_cmd), 1);
		if (!cmd)
			exit_error(cmd, "malloc", ERR_SYSTEM, EXIT_FAILURE);
		parse(cmd, line);
		free(line);
		//子プロセスにコマンドを実行させる
		child_process(cmd, envp);
		free_args(cmd->args);
		free(cmd);
	}
	return (0);
}
