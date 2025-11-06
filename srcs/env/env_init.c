/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:42:34 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/06 16:11:14 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	init_shell_vars(t_minishell *minishell, t_list **env_lst)
{
	t_status	status;

	status = set_pwd(minishell, env_lst);
	if (status == ERR_MALLOC)
		return (status);
	status = set_shlvl(env_lst);
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
		error_env_lst(minishell, head, "malloc", ERR_MALLOC);
		return (NULL);
	}
	status = init_shell_vars(minishell, &head);
	if (status == ERR_MALLOC)
	{
		error_env_lst(minishell, head, "malloc", ERR_MALLOC);
		return (NULL);
	}
	return (head);
}
