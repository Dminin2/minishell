/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:29:19 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/09 10:49:10 by hmaruyam         ###   ########.fr       */
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

static char	*join_with_slash(char *old_pwd, char *path)
{
	size_t	len;
	char	*tmp;
	char	*new_pwd;

	len = ft_strlen(old_pwd);
	if (len > 0 && old_pwd[len - 1] == '/')
		return (ft_strjoin(old_pwd, path));
	tmp = ft_strjoin(old_pwd, "/");
	if (!tmp)
		return (NULL);
	new_pwd = ft_strjoin(tmp, path);
	free(tmp);
	return (new_pwd);
}

static int	perform_chdir(t_list **env_lst, char *path)
{
	char	*old_pwd;
	char	*new_pwd;
	int		exit_status;

	old_pwd = search_env(*env_lst, "PWD");
	if (!old_pwd)
		old_pwd = "";
	if (chdir(path) == -1)
	{
		print_error_msg_builtin("cd", path, BLTERR_ERRNO);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		print_error_msg_builtin("cd", GETCWD_ERR, BLTERR_ERRNO);
		new_pwd = join_with_slash(old_pwd, path);
		if (!new_pwd)
			return (return_error("malloc", ERR_MALLOC));
	}
	exit_status = update_pwd_env(env_lst, old_pwd, new_pwd);
	free(new_pwd);
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
		ft_printf("%s\n", target_path);
	return (perform_chdir(&minishell->env_lst, target_path));
}
