/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:54:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/02 00:09:59 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	has_content(char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (!isspace(line[i]))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// void	parse(t_cmd *cmd, char *line)
// {
// 	if (!has_content(line))
// 		cmd->args = ft_split(line, 'A');
// 	else
// 		cmd->args = ft_split(line, ' ');
// }

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

void	print_redir_lst(t_list *head)
{
	t_redir	*redir;
	int		i;

	printf("---redir list---\n");
	i = 1;
	while (head)
	{
		redir = head->content;
		printf("<%d>\n", i);
		printf("value : %s\n", redir->value);
		if (redir->type == R_IN)
			printf("type : R_IN\n");
		else if (redir->type == R_OUT)
			printf("type : R_OUT\n");
		else if (redir->type == R_HEREDOC)
			printf("type : R_HEREDOC\n");
		else if (redir->type == R_APPEND)
			printf("type : R_APPEND\n");
		else
			printf("type : null\n");
		head = head->next;
		i++;
	}
}

void	print_cmd_lst(t_list *head)
{
	int		i;
	int		j;
	t_cmd	*cmd;

	i = 1;
	printf("-------cmd list--------\n");
	while (head)
	{
		printf("<<<%d>>>\n", i);
		cmd = head->content;
		j = 0;
		if (cmd->args)
		{
			while (cmd->args[j])
			{
				printf("word(%s) ", cmd->args[j]);
				j++;
			}
		}
		printf("\n");
		if (cmd->redir_lst)
			print_redir_lst(cmd->redir_lst);
		i++;
		head = head->next;
		if (head)
			printf("\n");
	}
}

void	print_pipeline(t_pipeline *pipeline)
{
	printf("cmds : %d\n", pipeline->n);
	print_cmd_lst(pipeline->cmd_lst);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_list		*lst;
	t_pipeline	*pipeline;

	// t_cmd		*cmd;
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		line = get_command_line();
		//入力終了
		if (!line)
			break ;
		lst = tokenize(line);
		free(line);
		if (!lst) // malloc失敗もしくはsytax error
			continue ;
		// debug用残しておきます
		// print_lst(lst);
		pipeline = parse(lst);
		ft_lstclear(&lst, &free_token_wrapper);
		if (!pipeline)
			continue ;
		print_pipeline(pipeline);
		free_pipeline(pipeline);
		//コマンド実行できるように残しておいただけなのでまだ未完成のparse
		// cmd = ft_calloc(sizeof(t_cmd), 1);
		// if (!cmd)
		// 	exit_error(cmd, "malloc", ERR_SYSTEM, EXIT_FAILURE);
		// parse(cmd, line);
		//子プロセスにコマンドを実行させる
		// parser作るときにt_cmdの中身変えて実行させるの面倒なので一旦コメントアウトします。
		// child_process(cmd, envp);
		// free_args(cmd->args);
		// free(cmd);
	}
	return (0);
}
