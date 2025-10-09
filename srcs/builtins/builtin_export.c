/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 23:15:17 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/09 18:54:31 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_no_args(t_list **env_array, size_t env_count)
{
	char	*env_value;
	char	*env_key;
	size_t	i;

	i = 0;
	while (i < env_count)
	{
		env_key = ((t_env *)(env_array[i]->content))->key;
		env_value = ((t_env *)(env_array[i]->content))->value;
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_key, STDOUT_FILENO);
		if (env_value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			print_escape_value(env_value);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
}

static int	handle_no_args(t_minishell *minishell)
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

static t_status	process_export_args(t_minishell *minishell, char *key,
		char *arg, int *last_status)
{
	if (!is_valid_identifier(key))
	{
		print_error_msg_builtin("export", arg, BLTERR_NOT_VALID);
		*last_status = 1;
	}
	else
	{
		return (process_env_line(&(minishell->env_lst), arg));
	}
	return (0);
}

static int	handle_args(t_minishell *minishell, char **args)
{
	int			i;
	int			last_status;
	char		*equal_pos;
	char		*key;
	t_status	status;

	i = 1;
	last_status = 0;
	while (args[i])
	{
		equal_pos = ft_strchr(args[i], '=');
		if (equal_pos == NULL)
			key = ft_strdup(args[i]);
		else
			key = ft_substr(args[i], 0, equal_pos - args[i]);
		if (!key)
			return (return_error("malloc", ERR_MALLOC));
		status = process_export_args(minishell, key, args[i], &last_status);
		free(key);
		if (status == ERR_MALLOC)
			return (return_error("malloc", ERR_MALLOC));
		i++;
	}
	return (last_status);
}

int	builtin_export(t_minishell *minishell, char **args)
{
	int	last_status;

	last_status = 0;
	if (!args[1])
		last_status = handle_no_args(minishell);
	else
		last_status = handle_args(minishell, args);
	return (last_status);
}
