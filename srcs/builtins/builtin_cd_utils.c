/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 22:00:00 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/22 22:00:00 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_arg_path(t_list *env_lst, char *arg)
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

char	*append_slash(char *path)
{
	char	*tmp;

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

char	*normalize_path(const char *unnormalized_abs_path)
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
