/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:29:19 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/30 00:04:17 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd_env(t_list **env_lst, char *old_pwd, char *new_pwd)
{
	t_status	status;

	status = process_env_key_value(env_lst, "OLDPWD", old_pwd);
	if (status == ERR_MALLOC)
		return (return_error("malloc", ERR_MALLOC));
	status = process_env_key_value(env_lst, "PWD", new_pwd);
	if (status == ERR_MALLOC)
		return (return_error("malloc", ERR_MALLOC));
	return (0);
}

static char	*build_absolute_path(t_minishell *minishell, char *arg)
{
	char	*cwd;
	char	*abs_path;
	char	*tmp;

	if (arg[0] == '/')
		return (ft_strdup(arg));
	if (!minishell->cwd)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			ft_dprintf(STDERR_FILENO, "chdir: %s: %s\n", GETCWD_ERR,
				strerror(errno));
			return (ft_strdup(arg));
		}
		minishell->cwd = cwd;
	}
	if (ft_strlen(minishell->cwd) > 1)
		tmp = ft_strjoin(minishell->cwd, "/");
	else
		tmp = ft_strdup(minishell->cwd);
	if (!tmp)
		return (NULL);
	abs_path = ft_strjoin(tmp, arg);
	free(tmp);
	return (abs_path);
}

static int	update_cwd(t_minishell *minishell, char *target_path,
		int normalize_failed)
{
	char	*getcwd_result;

	if (normalize_failed)
	{
		getcwd_result = getcwd(NULL, 0);
		if (getcwd_result)
		{
			free(minishell->cwd);
			minishell->cwd = getcwd_result;
			return (0);
		}
		ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", GETCWD_ERR, strerror(errno));
	}
	free(minishell->cwd);
	minishell->cwd = ft_strdup(target_path);
	if (!minishell->cwd)
		return (return_error("malloc", ERR_MALLOC));
	return (0);
}

static int	try_chdir_and_update(t_minishell *minishell, char *target_path,
		char *arg, t_normalize_status normalize_status)
{
	int		first_errno;
	int		normalize_failed;
	char	*old_pwd;

	normalize_failed = (normalize_status == NORMALIZE_STAT_FAILED);
	if (chdir(target_path) == 0)
	{
		if (update_cwd(minishell, target_path, normalize_failed) != 0)
			return (1);
		old_pwd = search_env(minishell->env_lst, "PWD");
		if (!old_pwd)
			old_pwd = "";
		return (update_pwd_env(&minishell->env_lst, old_pwd, minishell->cwd));
	}
	first_errno = errno;
	if (chdir(arg) == 0)
	{
		if (update_cwd(minishell, target_path, 1) != 0)
			return (1);
		old_pwd = search_env(minishell->env_lst, "PWD");
		if (!old_pwd)
			old_pwd = "";
		return (update_pwd_env(&minishell->env_lst, old_pwd, minishell->cwd));
	}
	ft_dprintf(STDERR_FILENO, "cd: %s: %s\n", arg, strerror(first_errno));
	return (1);
}

int	builtin_cd(t_minishell *minishell, char **args)
{
	char				*arg;
	char				*abs_path;
	char				*target_path;
	t_normalize_status	normalize_status;
	int					exit_status;
	char				*oldpwd;

	if (args[1] && args[2])
	{
		print_error_msg_builtin("cd", NULL, BLTERR_MANY_ARG);
		return (1);
	}
	oldpwd = NULL;
	if (args[1] && ft_strncmp(args[1], "-", 2) == 0)
	{
		if (search_env(minishell->env_lst, "OLDPWD"))
			oldpwd = ft_strdup(search_env(minishell->env_lst, "OLDPWD"));
	}
	arg = get_arg_path(minishell->env_lst, args[1]);
	if (!arg)
	{
		free(oldpwd);
		return (1);
	}
	abs_path = build_absolute_path(minishell, arg);
	if (!abs_path)
	{
		free(arg);
		free(oldpwd);
		return (return_error("malloc", ERR_MALLOC));
	}
	normalize_status = normalize_path(abs_path, &target_path);
	free(abs_path);
	if (normalize_status == NORMALIZE_MALLOC_ERROR)
	{
		free(arg);
		free(oldpwd);
		return (return_error("malloc", ERR_MALLOC));
	}
	exit_status = try_chdir_and_update(minishell, target_path, arg,
			normalize_status);
	free(target_path);
	if (exit_status == 0 && oldpwd)
		ft_printf("%s\n", oldpwd);
	free(arg);
	free(oldpwd);
	return (exit_status);
}
