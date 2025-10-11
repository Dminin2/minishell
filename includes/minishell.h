/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:54:21 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/11 19:05:07 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtin.h"
# include "common.h"
# include "debug.h"
# include "env.h"
# include "execute.h"
# include "expander.h"
# include "lexer.h"
# include "libft.h"
# include "parser.h"
# include "readline.h"
# include "redirection.h"
# include "utils.h"

# ifdef DEBUG
extern int	g_fd;
# endif

#endif
