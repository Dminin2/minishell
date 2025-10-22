/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:29:19 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/22 14:35:33 by hmaruyam         ###   ########.fr       */
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

static int	perform_chdir(t_list **env_lst, char *path, char *fallback_path)
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

	env_pwd = search_env(env_lst, "PWD");
	if (env_pwd && is_pwd_valid(env_pwd))
	{
		*cwd_out = ft_strdup(env_pwd);
		if (!*cwd_out)
			return (CWD_MALLOC_ERROR);
		return (CWD_SUCCESS);
	}
	*cwd_out = getcwd(NULL, 0);
	if (!*cwd_out)
		return (CWD_GETCWD_ERROR);
	return (CWD_SUCCESS);
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

static int	validate_component_path(char **components, int count)
{
	char		*current_path;
	struct stat	st;

	current_path = reconstruct_path(components, count);
	if (!current_path)
		return (0);
	if (lstat(current_path, &st) != 0)
	{
		free(current_path);
		return (0);
	}
	free(current_path);
	return (1);
}

static int	process_component(char **components, int *count, char *comp)
{
	if (ft_strcmp(comp, ".") == 0)
		return (1);
	if (ft_strcmp(comp, "..") == 0)
	{
		if (*count > 0)
			(*count)--;
		return (1);
	}
	components[*count] = comp;
	(*count)++;
	return (validate_component_path(components, *count));
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
	components = malloc(sizeof(char *) * i);
	if (!components)
	{
		free_args(split_path);
		return (NULL);
	}
	count = 0;
	i = 0;
	while (split_path[i])
	{
		if (!process_component(components, &count, split_path[i]))
		{
			free(components);
			free_args(split_path);
			return (NULL);
		}
		i++;
	}
	normalized_path = reconstruct_path(components, count);
	free(components);
	free_args(split_path);
	return (normalized_path);
}

static int	handle_absolute_path(t_list **env_lst, char *target_path)
{
	char	*normalized_path;
	int		exit_status;

	normalized_path = normalize_path(target_path);
	if (!normalized_path)
		return (return_error("malloc", ERR_MALLOC));
	exit_status = perform_chdir(env_lst, normalized_path, target_path);
	free(normalized_path);
	return (exit_status);
}

static int	handle_relative_path(t_list **env_lst, char *target_path)
{
	char			*cwd;
	char			*tmp;
	char			*unnormalized_abs_path;
	char			*normalized_path;
	int				exit_status;
	t_cwd_status	status;

	status = get_cwd_for_abs(*env_lst, &cwd);
	if (status == CWD_MALLOC_ERROR)
		return (return_error("malloc", ERR_MALLOC));
	if (status == CWD_GETCWD_ERROR)
		return (perform_chdir(env_lst, target_path, target_path));
	if (cwd[ft_strlen(cwd) - 1] != '/')
	{
		tmp = ft_strjoin(cwd, "/");
		free(cwd);
		if (!tmp)
			return (return_error("malloc", ERR_MALLOC));
		cwd = tmp;
	}
	unnormalized_abs_path = ft_strjoin(cwd, target_path);
	free(cwd);
	if (!unnormalized_abs_path)
		return (return_error("malloc", ERR_MALLOC));
	normalized_path = normalize_path(unnormalized_abs_path);
	free(unnormalized_abs_path);
	if (!normalized_path)
		return (return_error("malloc", ERR_MALLOC));
	exit_status = perform_chdir(env_lst, normalized_path, normalized_path);
	free(normalized_path);
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
	if (target_path[0] == '/')
		return (handle_absolute_path(&minishell->env_lst, target_path));
	else
		return (handle_relative_path(&minishell->env_lst, target_path));
}
