/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 22:00:00 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/28 23:57:30 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_arg_path(t_list *env_lst, char *arg)
{
	char	*env_value;
	char	*result;

	if (!arg)
	{
		env_value = search_env(env_lst, "HOME");
		if (!env_value)
		{
			print_error_msg_builtin("cd", NULL, BLTERR_NO_SET_HOME);
			return (NULL);
		}
		result = ft_strdup(env_value);
	}
	else if (ft_strncmp(arg, "-", 2) == 0)
	{
		env_value = search_env(env_lst, "OLDPWD");
		if (!env_value)
		{
			print_error_msg_builtin("cd", NULL, BLTERR_NO_SET_OLDPWD);
			return (NULL);
		}
		result = ft_strdup(env_value);
	}
	else
		result = ft_strdup(arg);
	if (!result)
	{
		return_error("malloc", ERR_MALLOC);
		return (NULL);
	}
	return (result);
}

char	*append_slash(char *path)
{
	char	*tmp;

	if (ft_strlen(path) == 0)
		return (path);
	if (path[ft_strlen(path) - 1] != '/')
	{
		tmp = ft_strjoin(path, "/");
		free(path);
		return (tmp);
	}
	return (path);
}

t_cwd_status	get_cwd_for_abs(t_list *env_lst, char **cwd_out)
{
	char	*env_pwd;

	*cwd_out = getcwd(NULL, 0);
	if (*cwd_out)
		return (CWD_FROM_GETCWD);
	env_pwd = search_env(env_lst, "PWD");
	if (env_pwd)
	{
		*cwd_out = ft_strdup(env_pwd);
		if (!*cwd_out)
			return (CWD_MALLOC_ERROR);
		return (CWD_FROM_PWD);
	}
	return (CWD_NOT_AVAILABLE);
}
