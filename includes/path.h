/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 13:30:36 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/06 13:36:12 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include "common.h"
# include <stdlib.h>

typedef enum e_normalize_status
{
	NORMALIZE_SUCCESS,
	NORMALIZE_STAT_FAILED,
	NORMALIZE_MALLOC_ERROR
}					t_normalize_status;

t_normalize_status	normalize_path(const char *abs_path, char **result);

void				remove_last_component(char *path);
char				*append_component(char *path, char *component);

#endif
