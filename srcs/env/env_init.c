/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:42:34 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/16 16:44:27 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	get_key_from_line(t_env *env, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			break ;
		i++;
	}
	env->key = ft_substr(line, 0, i);
	if (!env->key)
		return (ERR_MALLOC);
	else
		return (SUCCESS);
}

t_status	get_value_from_line(t_env *env, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	if (line[i] == '\0')
		env->value = ft_strdup("");
	else
		env->value = ft_substr(line, i + 1, ft_strlen(line) - (i + 1));
	if (!env->value)
		return (ERR_MALLOC);
	else
		return (SUCCESS);
}

t_list	*env_init(char **envp)
{
	t_list		*head;
	t_env		*env;
	int			i;
	t_status	status;

	i = 0;
	head = NULL;
	if (envp)
	{
		while (envp[i])
		{
			env = ft_calloc(1, sizeof(t_env));
			if (!env)
			{
				assert_error_env_init(head, "malloc", ERR_SYSTEM);
				return (NULL);
			}
			status = get_key_from_line(env, envp[i]);
			if (status != SUCCESS)
			{
				free_env(env);
				assert_error_env_init(head, "malloc", ERR_SYSTEM);
				return (NULL);
			}
			status = get_value_from_line(env, envp[i]);
			if (status != SUCCESS)
			{
				free_env(env);
				assert_error_env_init(head, "malloc", ERR_SYSTEM);
				return (NULL);
			}
			status = add_newlst(&head, env);
			if (status != SUCCESS)
			{
				free_env(env);
				assert_error_env_init(head, "malloc", ERR_SYSTEM);
				return (NULL);
			}
			i++;
		}
	}
	return (head);
}
