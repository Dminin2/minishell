/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 22:00:00 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/31 14:28:44 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare_oldpwd(t_list *env_lst, char **oldpwd_to_print)
{
	char	*tmp_oldpwd;

	tmp_oldpwd = search_env(env_lst, "OLDPWD");
	if (tmp_oldpwd)
	{
		*oldpwd_to_print = ft_strdup(tmp_oldpwd);
		if (!*oldpwd_to_print)
			return (return_error("malloc", ERR_MALLOC));
	}
	return (0);
}

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
		print_error_msg("malloc", ERR_MALLOC);
		return (NULL);
	}
	return (result);
}
