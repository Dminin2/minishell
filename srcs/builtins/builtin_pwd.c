/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 09:53:08 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/08 22:54:49 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_pwd_valid(char *env_pwd)
{
	struct stat	stat_of_current;
	struct stat	stat_of_pwd;

	if (stat(".", &stat_of_current) == -1)
		return (0);
	if (stat(env_pwd, &stat_of_pwd) == -1)
		return (0);
	if (stat_of_current.st_ino == stat_of_pwd.st_ino)
		return (1);
	return (0);
}

int	builtin_pwd(t_minishell *minishell)
{
	char	*cwd;
	char	*env_pwd;

	env_pwd = search_env(minishell->env_lst, "PWD");
	if (is_pwd_valid(env_pwd))
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
