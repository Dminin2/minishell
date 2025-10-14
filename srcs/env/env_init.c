/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:42:34 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/14 20:35:54 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	init_shell_vars(t_list **head)
{
	char	*cwd;
	char	*shlvl_str;
	int		shlvl_num;
	char	*existing_shlvl;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		printf(INIT_GETCWD_ERR "\n");
		return (ERR_INIT_GETCWD);
	}
	add_env(head, "PWD", cwd);
	free(cwd);
	shlvl_num = 1;
	existing_shlvl = search_env(*head, "SHLVL");
	if (existing_shlvl)
		shlvl_num = ft_atoi(existing_shlvl) + 1;
	if (shlvl_num > 999)
	{
		printf(SHLVL_ERR "shell level (%d) too high, resetting to 1\n",
			shlvl_num);
		shlvl_num = 1;
	}
	shlvl_str = ft_itoa(shlvl_num);
	if (!shlvl_str)
	{
		print_error_msg("malloc", ERR_MALLOC);
		return (ERR_MALLOC);
	}
	add_env(head, "SHLVL", shlvl_str);
	free(shlvl_str);
	return (SUCCESS);
}

t_list	*env_init(t_minishell *minishell, char **envp)
{
	t_list		*head;
	t_status	status;
	int			i;

	i = 0;
	head = NULL;
	if (envp)
	{
		while (envp[i])
		{
			status = process_env_line(&head, envp[i]);
			if (status == ERR_MALLOC)
			{
				minishell->last_status = assert_error_lst(head, "malloc",
						ERR_SYSTEM, free_env_wrapper);
				return (NULL);
			}
			i++;
		}
	}
	status = init_shell_vars(&head);
	if (status != SUCCESS)
	{
		ft_lstclear(&head, free_env_wrapper);
		if (status == ERR_INIT_GETCWD)
			exit(0);
	}
	return (head);
}
