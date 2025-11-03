/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:13:45 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/15 21:56:16 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "builtin.h"
# include "libft.h"
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define SHLVL_ERR "shell level (%d) too high, resetting to 1\n"

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

t_list		*env_init(t_minishell *minishell, char **envp);

t_status	set_pwd(t_minishell *minishell, t_list **env_lst);
t_status	set_shlvl(t_list **head);

t_status	process_env_line(t_list **head, char *line);
t_env		*find_existing_env(t_list *env_lst, char *line);
t_status	replace_env_value(t_env *env, char *line);
t_status	get_env_from_line(t_env *env, char *line);
t_status	create_and_addlst(t_list **head, char *line);

char		*pack_line(char *key, char *value);
int			is_valid_key_first_char(char c);
int			is_valid_key_char(char c);

t_status	process_env_key_value(t_list **head, char *key, char *value);
void		remove_env(t_list **head, char *key);

char		*search_env(t_list *env_lst, char *key);

char		**pack_env(t_list *env_lst);

void		free_env_wrapper(void *env);
void		free_env(t_env *env);

#endif
