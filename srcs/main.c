/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:54:01 by aomatsud          #+#    #+#             */
/*   Updated: 2025/08/19 16:24:04 by aomatsud         ###   ########.fr       */
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
	{
		cmd->args = ft_split(line, 'A');
		if (cmd->args[0])
			cmd->path = ft_strdup(cmd->args[0]);
		else
			cmd->path = NULL;
	}
	else
	{
		cmd->args = ft_split(line, ' ');
		cmd->path = ft_strdup(cmd->args[0]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = get_command_line();
		if (!line)
			break ;
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			exit_error(cmd, "malloc", ERR_SYSTEM, EXIT_FAILURE);
		parse(cmd, line);
		free(line);
		child_process(cmd, envp);
		free_args(cmd->args);
		free(cmd);
	}
	return (0);
}
