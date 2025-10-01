/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:13:45 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/30 14:35:01 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

t_list		*env_init(char **envp);

t_env		*find_existing_env(t_list *env_lst, char *line);
t_status	replace_env_value(t_env *env, char *line);
t_status	get_env_from_line(t_env *env, char *line);
t_status	create_and_addlst(t_list **head, char *line);

char		*search_env(t_list *env_lst, char *key);

#endif
