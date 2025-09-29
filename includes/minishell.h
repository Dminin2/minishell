/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:54:21 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/26 12:34:29 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "debug.h"
# include "env.h"
# include "execute.h"
# include "expander.h"
# include "lexer.h"
# include "parser.h"
# include "readline.h"
# include "redirection.h"
# include "types.h"
# include "utils.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

#endif
