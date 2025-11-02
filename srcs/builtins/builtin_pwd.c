/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 09:53:08 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/02 18:13:34 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_minishell *minishell)
{
	char	*cwd;

	if (minishell->cwd)
		ft_printf("%s\n", minishell->cwd);
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			ft_dprintf(STDERR_FILENO, "pwd: %s: %s\n", GETCWD_ERR,
				strerror(errno));
			return (1);
		}
		ft_printf("%s\n", cwd);
		free(cwd);
	}
	return (0);
}
