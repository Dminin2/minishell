/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:29:19 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/31 14:28:31 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	update_cwd_and_env(t_minishell *minishell, char *target_path,
		int normalize_failed)
{
	char	*old_pwd;

	if (update_cwd(minishell, target_path, normalize_failed) != 0)
		return (1);
	old_pwd = search_env(minishell->env_lst, "PWD");
	if (!old_pwd)
		old_pwd = "";
	return (update_pwd_env(&minishell->env_lst, old_pwd, minishell->cwd));
}

static int	perform_chdir(t_minishell *minishell, char *target_path, char *arg,
		t_normalize_status normalize_status)
{
	int	first_errno;
	int	normalize_failed;

	normalize_failed = (normalize_status == NORMALIZE_STAT_FAILED);
	if (chdir(target_path) == 0)
		return (update_cwd_and_env(minishell, target_path, normalize_failed));
	first_errno = errno;
	if (chdir(arg) == 0)
		return (update_cwd_and_env(minishell, target_path, 1));
	ft_dprintf(STDERR_FILENO, "minishell: cd: %s: %s\n", arg,
		strerror(first_errno));
	return (1);
}

static char	*build_target_path(t_minishell *minishell, char *arg,
		t_normalize_status *normalize_status)
{
	char	*abs_path;
	char	*target_path;

	abs_path = build_absolute_path(minishell, arg);
	if (!abs_path)
	{
		print_error_msg("malloc", ERR_MALLOC);
		return (NULL);
	}
	*normalize_status = normalize_path(abs_path, &target_path);
	free(abs_path);
	if (*normalize_status == NORMALIZE_MALLOC_ERROR)
	{
		print_error_msg("malloc", ERR_MALLOC);
		return (NULL);
	}
	return (target_path);
}

int	builtin_cd(t_minishell *minishell, char **args)
{
	char				*arg;
	char				*target_path;
	int					exit_status;
	t_normalize_status	normalize_status;

	if (args[1] && args[2])
	{
		print_error_msg_builtin("cd", NULL, BLTERR_MANY_ARG);
		return (1);
	}
	arg = get_arg_path(minishell->env_lst, args[1]);
	if (!arg)
		return (1);
	target_path = build_target_path(minishell, arg, &normalize_status);
	if (!target_path)
	{
		free(arg);
		return (1);
	}
	exit_status = perform_chdir(minishell, target_path, arg, normalize_status);
	free(target_path);
	if (exit_status == 0 && args[1] && ft_strncmp(args[1], "-", 2) == 0)
		ft_printf("%s\n", arg);
	free(arg);
	return (exit_status);
}
