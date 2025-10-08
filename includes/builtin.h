/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:54:35 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/08 12:06:47 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "common.h"
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

#define GETCWD_ERR "error retrieving current directory: getcwd: cannot access parent directories"

typedef enum e_blt_error
{
	BLTERR_MSG,
	BLTERR_ERRNO
}	t_blt_error;

int	builtin_pwd(t_minishell *minishell);
int	builtin_echo(char **args);
int	builtin_cd(t_minishell *minishell, char **args);

#endif
