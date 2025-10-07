/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:54:35 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/07 15:56:00 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "common.h"
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_blt_error
{
	BLTERR_MSG,
	BLTERR_ERRNO
}	t_blt_error;

int	builtin_pwd(t_minishell *minishell);
int	builtin_echo(char **args);

#endif
