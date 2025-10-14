/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:42:34 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/13 15:12:13 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*env_init(t_minishell *minishell, char **envp)
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
				minishell->last_status = assert_error_lst(head, "malloc",
						ERR_SYSTEM, free_env_wrapper);
				return (NULL);
			}
			i++;
		}
	}
	return (head);
}
