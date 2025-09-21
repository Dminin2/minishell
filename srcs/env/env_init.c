/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:42:34 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/22 00:57:31 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	key_exists(t_list *env_lst, char *line)
{
	t_env	*env;
	size_t	key_len;

	while (env_lst)
	{
		env = env_lst->content;
		key_len = ft_strlen(env->key);
		if (ft_strncmp(env->key, line, key_len) == 0 && (line[key_len] == '='
				|| line[key_len] == '\0'))
			return (1);
		env_lst = env_lst->next;
	}
	return (0);
}

t_status	replace_env_value(t_list *env_lst, char *line)
{
	t_env	*env;
	size_t	key_len;
	char	*new_value;

	while (env_lst)
	{
		env = env_lst->content;
		key_len = ft_strlen(env->key);
		if (ft_strncmp(env->key, line, key_len) == 0 && (line[key_len] == '='
				|| line[key_len] == '\0'))
			break ;
		env_lst = env_lst->next;
	}
	if (!env_lst)
		return (FAILURE);
	if (line[key_len] == '\0')
		new_value = ft_strdup("");
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
		env->value = ft_strdup("");
	else
		env->value = ft_strdup(line + i + 1);
	if (!env->value)
		return (ERR_MALLOC);
	else
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
	if (status != SUCCESS)
		free_env(env);
	else
	{
		status = add_newlst(head, env);
		if (status != SUCCESS)
			free_env(env);
	}
	return (status);
}

t_list	*env_init(char **envp)
{
	t_list		*head;
	int			i;
	t_status	status;

	i = 0;
	head = NULL;
	if (envp)
	{
		while (envp[i])
		{
			if (key_exists(head, envp[i]))
			{
				status = replace_env_value(head, envp[i]);
				if (status != SUCCESS)
				{
					assert_error_env_init(head, "malloc", ERR_SYSTEM);
					return (NULL);
				}
			}
			else
			{
				status = create_and_addlst(&head, envp[i]);
				if (status == ERR_MALLOC)
				{
					assert_error_env_init(head, "malloc", ERR_SYSTEM);
					return (NULL);
				}
			}
			i++;
		}
	}
	return (head);
}
