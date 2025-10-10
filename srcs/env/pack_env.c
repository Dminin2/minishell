/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pack_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 02:14:31 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/10 19:59:47 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_lst(t_list *env_lst)
{
	int	n;

	n = 0;
	while (env_lst)
	{
		n++;
		env_lst = env_lst->next;
	}
	return (n);
}

char	**pack_env(t_list *env_lst)
{
	char	**envp;
	int		env_count;
	t_env	*env;
	int		i;

	env_count = count_env_lst(env_lst);
	envp = ft_calloc(env_count + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env_lst)
	{
		env = env_lst->content;
		envp[i] = pack_line(env->key, env->value);
		if (!envp[i])
		{
			free_args(envp);
			return (NULL);
		}
		env_lst = env_lst->next;
		i++;
	}
	return (envp);
}
