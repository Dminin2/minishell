/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 12:30:00 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/06 15:25:05 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	process_append_arg(t_minishell *minishell, char *key,
		char *to_append_value)
{
	char		*new_value;
	char		*old_value;
	t_status	status;

	old_value = search_env(minishell->env_lst, key);
	if (!old_value)
		old_value = "";
	new_value = ft_strjoin(old_value, to_append_value);
	if (!new_value)
		return (ERR_MALLOC);
	status = process_env_key_value(&(minishell->env_lst), key, new_value);
	free(new_value);
	return (status);
}

static int	is_valid_identifier(char *key)
{
	int	i;

	if (!is_valid_key_first_char(key[0]))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!is_valid_key_char(key[i]))
			return (0);
		i++;
	}
	return (1);
}

static char	*extract_key(char *arg, int *is_append, char *equal_pos)
{
	if (equal_pos && equal_pos > arg && *(equal_pos - 1) == '+')
	{
		*is_append = 1;
		return (ft_substr(arg, 0, equal_pos - arg - 1));
	}
	else
	{
		*is_append = 0;
		if (!equal_pos)
			return (ft_strdup(arg));
		else
			return (ft_substr(arg, 0, equal_pos - arg));
	}
}

static t_status	handle_arg(t_minishell *minishell, char *arg, int *last_status)
{
	int			is_append;
	char		*equal_pos;
	char		*key;
	t_status	status;

	status = SUCCESS;
	equal_pos = ft_strchr(arg, '=');
	key = extract_key(arg, &is_append, equal_pos);
	if (!key)
		return (ERR_MALLOC);
	if (!is_valid_identifier(key))
	{
		print_error_msg_builtin("export", arg, BLTERR_NOT_VALID);
		*last_status = 1;
	}
	else
	{
		if (is_append)
			status = process_append_arg(minishell, key, equal_pos + 1);
		else
			status = process_env_line(&(minishell->env_lst), arg);
	}
	free(key);
	return (status);
}

int	handle_args(t_minishell *minishell, char **args)
{
	int			i;
	int			last_status;
	t_status	status;

	i = 1;
	last_status = 0;
	while (args[i])
	{
		status = handle_arg(minishell, args[i], &last_status);
		if (status == ERR_MALLOC)
		{
			set_builtin_malloc_error(minishell);
			return (2);
		}
		i++;
	}
	return (last_status);
}
