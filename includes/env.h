/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:13:45 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/03 01:16:33 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libft.h"
# include <stdlib.h>

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

void		free_env_wrapper(void *env);
void		free_env(t_env *env);

#endif
