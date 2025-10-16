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

static void	print_escape_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '`' || str[i] == '$' || str[i] == '\\')
			printf("\\");
		printf("%c", str[i]);
		i++;
	}
}

static void	print_no_args(t_list **env_array, size_t env_count)
{
	t_env	*env;
	size_t	i;

	i = 0;
	while (i < env_count)
	{
		env = (t_env *)(env_array[i]->content);
		if (ft_strcmp(env->key, "_") == 0)
		{
			i++;
			continue ;
		}
		printf("declare -x %s", env->key);
		if (env->value)
		{
			printf("=\"");
			print_escape_value(env->value);
			printf("\"");
		}
		printf("\n");
		i++;
	}
}

static void	bubble_sort_env_array(t_list **env_array, size_t env_count)
{
	size_t	i;
	size_t	j;
	t_list	*tmp;
	char	*key1;
	char	*key2;

	i = 0;
	while (i < env_count - 1)
	{
		j = 0;
		while (j < env_count - i - 1)
		{
			key1 = ((t_env *)(env_array[j]->content))->key;
			key2 = ((t_env *)(env_array[j + 1]->content))->key;
			if (ft_strcmp(key1, key2) > 0)
			{
				tmp = env_array[j];
				env_array[j] = env_array[j + 1];
				env_array[j + 1] = tmp;
			}
			j++;
		}
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
