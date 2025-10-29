/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:54:35 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/29 23:11:20 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "common.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# define GETCWD_ERR "error retrieving current directory: getcwd: cannot access parent directories"
# define NUMARG_ERR "numeric argument required"
# define ENV_ERR "not a valid identifier"

typedef enum e_blt_error
{
	BLTERR_NO_SET_HOME,
	BLTERR_NO_SET_OLDPWD,
	BLTERR_MANY_ARG,
	BLTERR_NOT_VALID,
	BLTERR_NUM_ARG,
	BLTERR_ERRNO
}		t_blt_error;

int		builtin_pwd(t_minishell *minishell);
int		builtin_echo(char **args);
int		builtin_cd(t_minishell *minishell, char **args);
int		builtin_export(t_minishell *minishell, char **args);
int		builtin_env(t_minishell *minishell);
int		builtin_unset(t_minishell *minishell, char **args);
int		builtin_exit(t_minishell *minishell, char **args, int cmd_count);

int		return_error(char *msg, t_status status);

int		handle_args(t_minishell *minishell, char **args);
int		handle_no_args(t_minishell *minishell);
int		strtouc_and_validate(char *str, unsigned char *last_status);

char	*get_arg_path(t_list *env_lst, char *arg);

#endif
