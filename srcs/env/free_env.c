/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 01:17:39 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/03 01:23:31 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_wrapper(void *env)
{
	free_env((t_env *)env);
}

void	free_env(t_env *env)
{
	if (env)
	{
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
	}
}
