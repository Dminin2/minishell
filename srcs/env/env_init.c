/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:42:34 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/03 11:21:41 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	process_env_line(t_list **head, char *line)
{
	t_env		*existing_env;
	t_status	status;

	existing_env = find_existing_env(*head, line);
	if (existing_env)
		status = replace_env_value(existing_env, line);
	else
		status = create_and_addlst(head, line);
	return (status);
}

t_list	*env_init(char **envp)
{
	t_list		*head;
	t_status	status;
	int			i;

	i = 0;
	head = NULL;
	if (envp)
	{
		while (envp[i])
		{
			status = process_env_line(&head, envp[i]);
			if (status == ERR_MALLOC)
			{
				assert_error_lst(head, "malloc", ERR_SYSTEM, free_env_wrapper);
				return (NULL);
			}
			i++;
		}
	}
	return (head);
}
