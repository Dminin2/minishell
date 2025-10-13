/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:27:22 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/11 15:41:00 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_lst(t_list *env_lst, int fd)
{
	t_env	*env;

	dprintf(fd, "=== env_lst ===\n");
	while (env_lst)
	{
		env = env_lst->content;
		dprintf(fd, "%s=%s\n", env->key, env->value);
		env_lst = env_lst->next;
	}
}
