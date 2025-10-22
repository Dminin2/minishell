/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:41:27 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/22 16:30:00 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_error(char *msg, t_status status)
{
	print_error_msg(msg, status);
	return (1);
}

int	is_pwd_valid(char *env_pwd)
{
	struct stat stat_of_current;
	struct stat stat_of_pwd;

	if (!env_pwd)
		return (0);
	if (stat(".", &stat_of_current) == -1)
		return (0);
	if (stat(env_pwd, &stat_of_pwd) == -1)
		return (0);
	if (stat_of_current.st_ino == stat_of_pwd.st_ino)
		return (1);
	return (0);
}
