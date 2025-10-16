/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 02:14:31 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/16 00:00:00 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_lst(t_list *env_lst)
{
	int		n;
	t_env	*env;

	n = 0;
	while (env_lst)
	{
		env = env_lst->content;
		if (env->value)
			n++;
		env_lst = env_lst->next;
	}
	return (n);
}

static char	**create_env_array(t_list *env_lst, char **envp)
{
	int		i;
	t_env	*env;

	i = 0;
	while (env_lst)
	{
		env = env_lst->content;
		if (env->value)
		{
			envp[i] = pack_line(env->key, env->value);
			if (!envp[i])
			{
				free_args(envp);
				return (NULL);
			}
			i++;
		}
		env_lst = env_lst->next;
	}
	return (envp);
}

char	**pack_env(t_list *env_lst)
{
	char	**envp;
	int		env_count;

	env_count = count_env_lst(env_lst);
	envp = ft_calloc(env_count + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	return (create_env_array(env_lst, envp));
}
