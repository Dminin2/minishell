/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 22:00:00 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/06 13:43:58 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_pwd_env(t_minishell *minishell, char *old_pwd, char *new_pwd)
{
	t_status	status;

	status = process_env_key_value(&(minishell->env_lst), "OLDPWD", old_pwd);
	if (status == ERR_MALLOC)
		return (return_error(minishell, "malloc", ERR_MALLOC));
	status = process_env_key_value(&(minishell->env_lst), "PWD", new_pwd);
	if (status == ERR_MALLOC)
		return (return_error(minishell, "malloc", ERR_MALLOC));
	return (0);
}

static char	*cd_env_error(t_blt_error error)
{
	print_error_msg_builtin("cd", NULL, error);
	return (NULL);
}

char	*get_arg_path(t_minishell *minishell, char *arg)
{
	char	*env_value;
	char	*result;

	if (!arg)
	{
		env_value = search_env(minishell->env_lst, "HOME");
		if (!env_value)
			return (cd_env_error(BLTERR_NO_SET_HOME));
		result = ft_strdup(env_value);
	}
	else if (ft_strncmp(arg, "-", 2) == 0)
	{
		env_value = search_env(minishell->env_lst, "OLDPWD");
		if (!env_value)
			return (cd_env_error(BLTERR_NO_SET_OLDPWD));
		result = ft_strdup(env_value);
	}
	else
		result = ft_strdup(arg);
	if (!result)
	{
		print_error_msg("malloc", ERR_MALLOC);
		minishell->should_exit = 1;
	}
	return (result);
}

static char	*join_cwd_and_arg(char *cwd, char *arg)
{
	char	*abs_path;
	char	*cwd_with_slash;

	if (ft_strlen(cwd) > 1 && cwd[ft_strlen(cwd) - 1] != '/')
		cwd_with_slash = ft_strjoin(cwd, "/");
	else
		cwd_with_slash = ft_strdup(cwd);
	if (!cwd_with_slash)
		return (NULL);
	abs_path = ft_strjoin(cwd_with_slash, arg);
	free(cwd_with_slash);
	return (abs_path);
}

char	*build_absolute_path(t_minishell *minishell, char *arg)
{
	char	*cwd;

	if (arg[0] == '/')
		return (ft_strdup(arg));
	if (!minishell->cwd)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			ft_dprintf_buf(STDERR_FILENO, "chdir: %s: %s\n", GETCWD_ERR,
				strerror(errno));
			return (ft_strdup(arg));
		}
		minishell->cwd = cwd;
	}
	return (join_cwd_and_arg(minishell->cwd, arg));
}
