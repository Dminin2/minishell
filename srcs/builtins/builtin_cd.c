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

static char	*get_arg_path(t_list *env_lst, char *arg)
{
	char	*arg_path;

	if (!arg)
	{
		arg_path = search_env(env_lst, "HOME");
		if (!arg_path)
			print_error_msg_builtin("cd", NULL, BLTERR_NO_SET_HOME);
	}
	else if (ft_strncmp(arg, "-", 2) == 0)
	{
		arg_path = search_env(env_lst, "OLDPWD");
		if (!arg_path)
			print_error_msg_builtin("cd", NULL, BLTERR_NO_SET_OLDPWD);
	}
	else
		arg_path = arg;
	return (arg_path);
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

static int	perform_chdir(t_list **env_lst, char *path, char *error_path,
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

static t_cwd_status	get_cwd_for_abs(t_list *env_lst, char **cwd_out)
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

static char	*reconstruct_path(char **components, int count)
{
	char	*path;
	char	*tmp;
	int		i;

	path = ft_strdup("/");
	if (!path)
		return (NULL);
	i = 0;
	while (i < count)
	{
		if (ft_strlen(path) > 1)
		{
			tmp = ft_strjoin(path, "/");
			free(path);
			if (!tmp)
				return (NULL);
			path = tmp;
		}
		tmp = ft_strjoin(path, components[i]);
		free(path);
		if (!tmp)
			return (NULL);
		path = tmp;
		i++;
	}
	return (path);
}

static void	process_component(char **components, int *count, char *component)
{
	if (ft_strcmp(component, ".") == 0)
		return ;
	if (ft_strcmp(component, "..") == 0)
	{
		if (*count > 0)
			(*count)--;
		return ;
	}
	components[*count] = component;
	(*count)++;
}

static char	*normalize_path(const char *unnormalized_abs_path)
{
	char	**split_path;
	char	**components;
	char	*normalized_path;
	int		i;
	int		count;

	split_path = ft_split(unnormalized_abs_path, '/');
	if (!split_path)
		return (NULL);
	i = 0;
	while (split_path[i])
		i++;
	components = ft_calloc(i, sizeof(char *));
	if (!components)
	{
		free_args(split_path);
		return (NULL);
	}
	count = 0;
	i = 0;
	while (split_path[i])
	{
		process_component(components, &count, split_path[i]);
		i++;
	}
	normalized_path = reconstruct_path(components, count);
	free(components);
	free_args(split_path);
	return (normalized_path);
}

static int	handle_absolute_path(t_list **env_lst, char *arg_path)
{
	char	*normalized_path;
	int		exit_status;

	normalized_path = normalize_path(arg_path);
	if (!normalized_path)
		return (return_error("malloc", ERR_MALLOC));
	exit_status = perform_chdir(env_lst, normalized_path, arg_path, NULL);
	free(normalized_path);
	return (exit_status);
}

static int	handle_relative_path(t_list **env_lst, char *arg_path)
{
	char			*cwd;
	char			*tmp;
	char			*abs_path;
	char			*normalized_path;
	int				exit_status;
	t_cwd_status	status;

	status = get_cwd_for_abs(*env_lst, &cwd);
	if (status == CWD_MALLOC_ERROR)
		return (return_error("malloc", ERR_MALLOC));
	if (status == CWD_NOT_AVAILABLE)
		return (perform_chdir(env_lst, arg_path, arg_path, arg_path));
	if (cwd[ft_strlen(cwd) - 1] != '/')
	{
		tmp = ft_strjoin(cwd, "/");
		free(cwd);
		if (!tmp)
			return (return_error("malloc", ERR_MALLOC));
		cwd = tmp;
	}
	abs_path = ft_strjoin(cwd, arg_path);
	free(cwd);
	if (!abs_path)
		return (return_error("malloc", ERR_MALLOC));
	normalized_path = normalize_path(abs_path);
	if (!normalized_path)
	{
		free(abs_path);
		return (return_error("malloc", ERR_MALLOC));
	}
	if (status == CWD_FROM_PWD)
		exit_status = perform_chdir(env_lst, arg_path, arg_path, abs_path);
	else
		exit_status = perform_chdir(env_lst, normalized_path, arg_path, NULL);
	free(normalized_path);
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
