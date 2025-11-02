/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:42:34 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/29 22:04:53 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	init_shell_vars(t_minishell *minishell, t_list **head)
{
	t_status	status;

	status = set_pwd(minishell, head);
	if (status == ERR_MALLOC)
		return (status);
	status = set_shlvl(head);
	if (status == ERR_MALLOC)
	{
		free(minishell->cwd);
		minishell->cwd = NULL;
		return (status);
	}
	return (status);
}

static t_status	create_env_list(t_list **head, char **envp)
{
	t_status	status;
	int			i;

	i = 0;
	if (!envp)
		return (SUCCESS);
	while (envp[i])
	{
		status = process_env_line(head, envp[i]);
		if (status == ERR_MALLOC)
			return (ERR_MALLOC);
		i++;
	}
	return (SUCCESS);
}

t_list	*env_init(t_minishell *minishell, char **envp)
{
	t_list		*head;
	t_status	status;

	head = NULL;
	status = create_env_list(&head, envp);
	if (status == ERR_MALLOC)
	{
		minishell->last_status = error_lst(head, "malloc", ERR_MALLOC,
				free_env_wrapper);
		return (NULL);
	}
	status = init_shell_vars(minishell, &head);
	if (status == ERR_MALLOC)
	{
		minishell->last_status = error_lst(head, "malloc", ERR_MALLOC,
				free_env_wrapper);
		return (NULL);
	}
	return (head);
}
