/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:54:35 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/10 12:05:14 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "common.h"
# include <limits.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define GETCWD_ERR "error retrieving current directory: getcwd: cannot access parent directories"

typedef enum e_blt_error
{
	BLTERR_NO_SET_HOME,
	BLTERR_NO_SET_OLDPWD,
	BLTERR_MANY_ARG,
	BLTERR_ERRNO
}	t_blt_error;

int	builtin_pwd(t_minishell *minishell);
int	builtin_echo(char **args);
int	builtin_cd(t_minishell *minishell, char **args);
int	builtin_env(t_minishell *minishell);

int	return_error(char *msg, t_status status);
#endif
