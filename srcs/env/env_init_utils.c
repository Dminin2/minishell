/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:02:50 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/02 18:02:51 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	prepare_cwd(t_minishell *minishell, t_list *env_lst, char **cwd)
{
	char				*env_pwd;
	t_normalize_status	normalize_status;

	env_pwd = search_env(env_lst, "PWD");
	if (is_pwd_valid(env_pwd))
	{
		normalize_status = normalize_path(env_pwd, cwd);
		if (normalize_status == NORMALIZE_MALLOC_ERROR)
			return (ERR_MALLOC);
		if (normalize_status == NORMALIZE_STAT_FAILED)
		{
			free(*cwd);
			*cwd = getcwd(NULL, 0);
		}
	}
	else
		*cwd = getcwd(NULL, 0);
	if (!*cwd)
	{
		ft_dprintf_buf(STDERR_FILENO, "shell-init: %s: %s\n", GETCWD_ERR,
			strerror(errno));
		minishell->cwd = NULL;
	}
	return (SUCCESS);
}

t_status	set_pwd(t_minishell *minishell, t_list **env_lst)
{
	t_status	status;
	char		*cwd;

	status = prepare_cwd(minishell, *env_lst, &cwd);
	if (status == ERR_MALLOC)
		return (status);
	if (!cwd)
		return (SUCCESS);
	status = process_env_key_value(env_lst, "PWD", cwd);
	if (status == ERR_MALLOC)
	{
		free(cwd);
		return (status);
	}
	minishell->cwd = cwd;
	return (status);
}

t_status	set_shlvl(t_list **head)
{
	char		*shlvl_str;
	int			shlvl_num;
	char		*existing_shlvl;
	t_status	status;

	shlvl_num = 1;
	existing_shlvl = search_env(*head, "SHLVL");
	if (existing_shlvl)
		shlvl_num = ft_atoi(existing_shlvl) + 1;
	if (shlvl_num > 999)
	{
		ft_dprintf_buf(STDERR_FILENO, "minishell: warning: " SHLVL_ERR,
			shlvl_num);
		shlvl_num = 1;
	}
	shlvl_str = ft_itoa(shlvl_num);
	if (!shlvl_str)
		return (ERR_MALLOC);
	status = process_env_key_value(head, "SHLVL", shlvl_str);
	free(shlvl_str);
	return (status);
}
