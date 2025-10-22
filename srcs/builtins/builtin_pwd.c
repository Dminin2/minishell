/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 09:53:08 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/22 16:35:00 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_minishell *minishell)
{
	char	*cwd;
	char	*env_pwd;

	env_pwd = search_env(minishell->env_lst, "PWD");
	if (env_pwd)
		ft_printf("%s\n", env_pwd);
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			print_error_msg_builtin("pwd", GETCWD_ERR, BLTERR_ERRNO);
			return (1);
		}
		ft_printf("%s\n", cwd);
		free(cwd);
	}
	return (0);
}
