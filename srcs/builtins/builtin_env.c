/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:52:45 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/09 21:39:50 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_list *env_lst)
{
	char	*env_key;
	char	*env_value;
	t_list	*cur_node;

	cur_node = env_lst;
	while (cur_node)
	{
		env_key = ((t_env *)(cur_node->content))->key;
		env_value = ((t_env *)(cur_node->content))->value;
		if (env_value)
		{
			ft_putstr_fd(env_key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(env_value, STDOUT_FILENO);
		}
		cur_node = cur_node->next;
	}
	return (0);
}
