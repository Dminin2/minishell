

#include "minishell.h"

t_status	set_pwd(t_minishell *minishell, t_list **head)
{
	char				*env_pwd;
	char				*cwd;
	t_status			status;
	t_normalize_status	normalize_status;

	env_pwd = search_env(*head, "PWD");
	if (is_pwd_valid(env_pwd))
	{
		normalize_status = normalize_path(env_pwd, &cwd);
		if (normalize_status == NORMALIZE_MALLOC_ERROR)
			return (ERR_MALLOC);
		if (normalize_status == NORMALIZE_STAT_FAILED)
		{
			free(cwd);
			cwd = getcwd(NULL, 0);
		}
	}
	else
		cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_dprintf(STDERR_FILENO, "shell-init: %s: %s\n", GETCWD_ERR,
			strerror(errno));
		minishell->cwd = NULL;
		return (SUCCESS);
	}
	status = process_env_key_value(head, "PWD", cwd);
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
		ft_dprintf(STDERR_FILENO, "minishell: warning: " SHLVL_ERR, shlvl_num);
		shlvl_num = 1;
	}
	shlvl_str = ft_itoa(shlvl_num);
	if (!shlvl_str)
		return (ERR_MALLOC);
	status = process_env_key_value(head, "SHLVL", shlvl_str);
	free(shlvl_str);
	return (status);
}
