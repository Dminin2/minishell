/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:29:19 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/22 21:39:59 by hmaruyam         ###   ########.fr       */
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

static int	exec_chdir(t_list **env_lst, char *path, char *error_path,
		char *fallback_path)
{
	char	*old_pwd;
	char	*new_pwd;
	int		exit_status;

	old_pwd = search_env(*env_lst, "PWD");
	if (!old_pwd)
		old_pwd = "";
	if (chdir(path) == -1)
	{
		print_error_msg_builtin("cd", error_path, BLTERR_ERRNO);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		print_error_msg_builtin("cd", GETCWD_ERR, BLTERR_ERRNO);
		new_pwd = ft_strdup(fallback_path);
		if (!new_pwd)
			return (return_error("malloc", ERR_MALLOC));
	}
	exit_status = update_pwd_env(env_lst, old_pwd, new_pwd);
	free(new_pwd);
	return (exit_status);
}

static int	handle_absolute_path(t_list **env_lst, char *arg_path)
{
	char	*clean_path;
	int		exit_status;

	clean_path = normalize_path(arg_path);
	if (!clean_path)
		return (return_error("malloc", ERR_MALLOC));
	exit_status = exec_chdir(env_lst, clean_path, arg_path, clean_path);
	free(clean_path);
	return (exit_status);
}

static int	handle_relative_path(t_list **env_lst, char *arg_path)
{
	char			*cwd;
	char			*abs_path;
	char			*clean_path;
	int				exit_status;
	t_cwd_status	status;

	status = get_cwd_for_abs(*env_lst, &cwd);
	if (status == CWD_MALLOC_ERROR)
		return (return_error("malloc", ERR_MALLOC));
	if (status == CWD_NOT_AVAILABLE)
		return (exec_chdir(env_lst, arg_path, arg_path, arg_path));
	cwd = append_slash(cwd);
	if (!cwd)
		return (return_error("malloc", ERR_MALLOC));
	abs_path = ft_strjoin(cwd, arg_path);
	free(cwd);
	if (!abs_path)
		return (return_error("malloc", ERR_MALLOC));
	clean_path = normalize_path(abs_path);
	if (!clean_path)
	{
		free(abs_path);
		return (return_error("malloc", ERR_MALLOC));
	}
	if (status == CWD_FROM_PWD)
		exit_status = exec_chdir(env_lst, arg_path, arg_path, abs_path);
	else
		exit_status = exec_chdir(env_lst, clean_path, arg_path, clean_path);
	free(clean_path);
	free(abs_path);
	return (exit_status);
}

int	builtin_cd(t_minishell *minishell, char **args)
{
	char	*arg_path;

	if (args[1] && args[2])
	{
		print_error_msg_builtin("cd", NULL, BLTERR_MANY_ARG);
		return (1);
	}
	arg_path = get_arg_path(minishell->env_lst, args[1]);
	if (!arg_path)
		return (1);
	if (args[1] && ft_strncmp(args[1], "-", 2) == 0)
		ft_printf("%s\n", arg_path);
	if (arg_path[0] == '/')
		return (handle_absolute_path(&minishell->env_lst, arg_path));
	else
		return (handle_relative_path(&minishell->env_lst, arg_path));
}
