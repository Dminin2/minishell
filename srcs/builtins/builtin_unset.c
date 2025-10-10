/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 10:30:54 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/10 11:27:32 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_minishell *minishell, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env(&minishell->env_lst, args[i]);
		i++;
	}
	return (0);
}
