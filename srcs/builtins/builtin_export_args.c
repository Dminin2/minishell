/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 12:30:00 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/12 16:30:09 by hmaruyam         ###   ########.fr       */
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

static t_status	process_export_arg(t_minishell *minishell, char *arg)
{
	return (process_env_line(&(minishell->env_lst), arg));
}

static char	*extract_key(char *arg, bool *is_append, char *equal_pos)
{
	if (equal_pos && equal_pos > arg && *(equal_pos - 1) == '+')
	{
		*is_append = true;
		return (ft_substr(arg, 0, equal_pos - arg - 1));
	}
	else
	{
		*is_append = false;
		if (!equal_pos)
			return (ft_strdup(arg));
		else
			return (ft_substr(arg, 0, equal_pos - arg));
	}
}

static t_status	handle_arg(t_minishell *minishell, char *arg, int *last_status)
{
	bool		is_append;
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
			status = process_export_arg(minishell, arg);
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
			return (return_error("malloc", ERR_MALLOC));
		i++;
	}
	return (last_status);
}
