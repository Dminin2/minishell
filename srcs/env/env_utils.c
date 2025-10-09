/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:27:13 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/08 22:47:53 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_existing_env(t_list *env_lst, char *line)
{
	t_env	*env;
	size_t	key_len;

	while (env_lst)
	{
		env = env_lst->content;
		key_len = ft_strlen(env->key);
		if (ft_strncmp(env->key, line, key_len) == 0 && (line[key_len] == '='
				|| line[key_len] == '\0'))
			return (env);
		env_lst = env_lst->next;
	}
	return (NULL);
}

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

t_status	get_env_from_line(t_env *env, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (i == 0)
		return (FAILURE);
	env->key = ft_substr(line, 0, i);
	if (!env->key)
		return (ERR_MALLOC);
	if (line[i] == '\0')
		env->value = NULL;
	else
	{
		env->value = ft_strdup(line + i + 1);
		if (!env->value)
			return (ERR_MALLOC);
	}
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
