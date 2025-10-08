/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:17:15 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/08 22:17:26 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	add_env(t_list **head, char *key, char *value)
{
	char *line;
	char *tmp;
	t_status status;

	if (!key || !value)
		return (FAILURE);
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (ERR_MALLOC);
	line = ft_strjoin(tmp, value);
	free(tmp);
	if (!line)
		return (ERR_MALLOC);
	status = process_env_line(head, line);
	free(line);
	return (status);
}
