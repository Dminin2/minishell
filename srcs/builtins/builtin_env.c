/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:52:45 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/09 21:48:16 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_list *env_lst)
{
	t_list	*cur_node;
	t_env	*env;

	cur_node = env_lst;
	while (cur_node)
	{
		env = (t_env *)(cur_node->content);
		if (env->value)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(env->value, STDOUT_FILENO);
		}
		cur_node = cur_node->next;
	}
	return (0);
}
