/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 23:39:55 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/23 23:43:43 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_env(t_list *env_lst, char *key)
{
	t_env	*env;

	while (env_lst)
	{
		env = env_lst->content;
		if (ft_strncmp(key, env->key, ft_strlen(env->key) + 1) == 0)
			return (env->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}
