/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:29:19 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/08 15:17:35 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_target_path(t_list *env_lst, char *arg)
{
	char	*target_path;

	if (!arg)
	{
		target_path = search_env(env_lst, "HOME");
		if (!target_path)
			print_error_msg_builtin("cd", NULL, BLTERR_NO_SET_HOME);
	}
	else if (ft_strncmp(arg, "-", 2) == 0)
	{
		target_path = search_env(env_lst, "OLDPWD");
		if (!target_path)
			print_error_msg_builtin("cd", NULL, BLTERR_NO_SET_OLDPWD);
	}
	else
		target_path = arg;
	return (target_path);
}

static int	report_error(char *msg, int err_type)
{
	print_error_msg(msg, err_type);
	return (1);
}

static int	update_pwd_env(t_list **env_lst, char *old_pwd, char *new_pwd)
{
	char		*pwd_line;
	t_status	status;

	pwd_line = ft_strjoin("OLDPWD=", old_pwd);
	if (!pwd_line)
		return (report_error("malloc", ERR_SYSTEM));
	status = process_env_line(env_lst, pwd_line);
	free(pwd_line);
	if (status == ERR_MALLOC)
		return (report_error("malloc", ERR_SYSTEM));
	pwd_line = ft_strjoin("PWD=", new_pwd);
	if (!pwd_line)
		return (report_error("malloc", ERR_SYSTEM));
	status = process_env_line(env_lst, pwd_line);
	free(pwd_line);
	if (status == ERR_MALLOC)
		return (report_error("malloc", ERR_SYSTEM));
	return (0);
}

static int	perform_chdir(t_list **env_lst, char *path)
{
	char	*old_pwd;
	char	new_pwd[PATH_MAX];
	int		exit_status;

	old_pwd = search_env(*env_lst, "PWD");
	if (!old_pwd)
		old_pwd = "";
	if (chdir(path) == -1)
	{
		print_error_msg_builtin("cd", path, BLTERR_ERRNO);
		return (1);
	}
	if (!getcwd(new_pwd, PATH_MAX))
	{
		print_error_msg_builtin("cd", GETCWD_ERR, BLTERR_ERRNO);
		return (1);
	}
	exit_status = update_pwd_env(env_lst, old_pwd, new_pwd);
	return (exit_status);
}

int	builtin_cd(t_minishell *minishell, char **args)
{
	char	*target_path;

	if (args[1] && args[2])
	{
		print_error_msg_builtin("cd", NULL, BLTERR_MANY_ARG);
		return (1);
	}
	target_path = get_target_path(minishell->env_lst, args[1]);
	if (!target_path)
		return (1);
	if (args[1] && ft_strncmp(args[1], "-", 2) == 0)
		ft_putendl_fd(target_path, STDOUT_FILENO);
	return (perform_chdir(&minishell->env_lst, target_path));
}
