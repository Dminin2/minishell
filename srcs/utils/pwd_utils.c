/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:58:53 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/28 15:58:54 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pwd_valid(char *pwd_path)
{
	struct stat	stat_of_current;
	struct stat	stat_of_pwd;

	if (!pwd_path || pwd_path[0] != '/')
		return (0);
	if (stat(".", &stat_of_current) == -1)
		return (0);
	if (stat(pwd_path, &stat_of_pwd) == -1)
		return (0);
	if (stat_of_current.st_ino == stat_of_pwd.st_ino)
		return (1);
	return (0);
}
