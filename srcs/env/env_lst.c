/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:06:41 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/10 16:07:14 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	replace_env_value(t_env *env, char *line)
{
	size_t	key_len;
	char	*new_value;

	key_len = ft_strlen(env->key);
	if (line[key_len] == '\0')
	{
		if (env->value)
			new_value = ft_strdup("");
		else
			return (SUCCESS);
	}
	else
		new_value = ft_strdup(line + key_len + 1);
	if (!new_value)
		return (ERR_MALLOC);
	free(env->value);
	env->value = new_value;
	return (SUCCESS);
}

t_status	create_and_addlst(t_list **head, char *line)
{
	t_env		*env;
	t_status	status;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (ERR_MALLOC);
	status = get_env_from_line(env, line);
	if (status == SUCCESS)
		status = add_newlst(head, env);
	if (status != SUCCESS)
		free_env(env);
	return (status);
}

t_status	process_env_line(t_list **head, char *line)
{
	t_env		*existing_env;
	t_status	status;

	existing_env = find_existing_env(*head, line);
	if (existing_env)
		status = replace_env_value(existing_env, line);
	else
		status = create_and_addlst(head, line);
	return (status);
}
