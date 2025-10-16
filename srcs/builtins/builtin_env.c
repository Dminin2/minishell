/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:52:45 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/10 12:05:28 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_minishell *minishell)
{
	t_list	*cur_node;
	t_env	*env;

	cur_node = minishell->env_lst;
	while (cur_node)
	{
		env = (t_env *)(cur_node->content);
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		cur_node = cur_node->next;
	}
	return (0);
}
