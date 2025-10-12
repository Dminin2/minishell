/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_no_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 12:30:00 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/12 16:24:18 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_no_args(t_list **env_array, size_t env_count)
{
	t_env	*env;
	size_t	i;

	i = 0;
	while (i < env_count)
	{
		env = ((t_env *)(env_array[i]->content));
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->key, STDOUT_FILENO);
		if (env->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			print_escape_value(env->value);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
}

int	handle_no_args(t_minishell *minishell)
{
	t_list	**env_array;
	t_list	*current_node;
	size_t	env_count;
	size_t	i;

	env_count = ft_lstsize(minishell->env_lst);
	if (env_count == 0)
		return (0);
	env_array = ft_calloc(env_count, sizeof(t_list *));
	if (!env_array)
		return (return_error("malloc", ERR_MALLOC));
	current_node = minishell->env_lst;
	i = 0;
	while (current_node)
	{
		env_array[i++] = current_node;
		current_node = current_node->next;
	}
	bubble_sort_env_array(env_array, env_count);
	print_no_args(env_array, env_count);
	free(env_array);
	return (0);
}
