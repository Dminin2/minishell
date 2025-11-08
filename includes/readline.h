/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:17:56 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/08 14:56:58 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include "common.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>

# define PROMPT_PART1_SUCCESS "\001\033[32m\002minishell\001\033[0m\002 \
> \001\033[34m\033[1m\002"
# define PROMPT_PART1_ERROR "\001\033[32m\002minishell\001\033[0m\002 \001\033[31m\002\
>\001\033[0m\002 \001\033[34m\033[1m\002"
# define PROMPT_PART2 "\001\033[0m\002 $ "

typedef struct s_input
{
	char	*line;
	int		is_eof;
}			t_input;

t_input		*get_command_line(t_minishell *minishell);
void		free_input(t_input *input);

#endif
