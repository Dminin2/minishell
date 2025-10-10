/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:17:15 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/10 11:16:57 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	add_env(t_list **head, char *key, char *value)
{
	char		*line;
	char		*tmp;
	t_status	status;

	if (!value)
		status = process_env_line(head, key);
	else
	{
		tmp = ft_strjoin(key, "=");
		if (!tmp)
			return (ERR_MALLOC);
		line = ft_strjoin(tmp, value);
		free(tmp);
		if (!line)
			return (ERR_MALLOC);
		status = process_env_line(head, line);
		free(line);
	}
	return (status);
}

void	remove_env(t_list **head, char *key)
{
	t_list	*current;
	t_list	*prev;
	t_env	*env;

	current = *head;
	while (current)
	{
		env = current->content;
		if (ft_strcmp(env->key, key) == 0)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			ft_lstdelone(current, free_env_wrapper);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
