/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:17:56 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/06 11:00:20 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include "common.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>

# define PROMPT_PART1_SUCCESS "\033[32mminishell\033[0m ➜ \033[34m\033[1m"
# define PROMPT_PART1_ERROR "\033[32mminishell\033[0m \033[31m➜\033[0m \033[34m\033[1m"
# define PROMPT_PART2 "\033[0m $ "

typedef struct s_input
{
	char	*line;
	int		is_eof;
}			t_input;

t_input		*get_command_line(t_minishell *minishell);
void		free_input(t_input *input);

#endif
