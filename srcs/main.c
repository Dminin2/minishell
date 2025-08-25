/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:54:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/08/23 18:49:01 by aomatsud         ###   ########.fr       */
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

void	print_lst(t_list *lst)
{
	t_token	*tok;

	while (lst)
	{
		tok = lst->content;
		if (tok->value)
			printf("%s\n", tok->value);
		else
			printf("%d\n", tok->type);
		lst = lst->next;
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
		if (!line)
			break ;
		cmd = ft_calloc(sizeof(t_cmd), 1);
		if (!cmd)
			exit_error(cmd, "malloc", ERR_SYSTEM, EXIT_FAILURE);
		lst = tokenize(line);
		parse(cmd, line);
		free(line);
		if (!lst)
			continue ;
		print_lst(lst);
		ft_lstclear(&lst, (void (*)(void *))free_token);
		child_process(cmd, envp);
		free_args(cmd->args);
		free(cmd);
	}
	return (0);
}
