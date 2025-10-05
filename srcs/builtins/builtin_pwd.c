/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 09:53:08 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/05 14:57:51 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_pwd_valid(char *env_pwd)
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
	if (env_pwd && is_pwd_valid(env_pwd))
		ft_putendl_fd(env_pwd, STDOUT_FILENO);
	else
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			print_error_msg("getcwd", ERR_SYSTEM);
			return (1);
		}
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free(cwd);
	}
	return (0);
}
