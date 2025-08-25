/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:17:00 by aomatsud          #+#    #+#             */
/*   Updated: 2025/08/25 22:13:35 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->args)
			free_args(cmd->args);
		if (cmd->path)
			free(cmd->path);
		free(cmd);
	}
}

void	free_token_wrapper(void *tok)
{
	free_token((t_token *)tok);
}

void	free_token(t_token *tok)
{
	if (tok)
	{
		if (tok->value)
			free(tok->value);
		free(tok);
	}
}
