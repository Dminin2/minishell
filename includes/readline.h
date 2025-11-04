/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:17:56 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/04 22:44:09 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include "common.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>

# define C_RESET "\033[0m"
# define C_GREEN "\033[32m"
# define C_BLUE "\033[34m"
# define C_BOLD "\033[1m"
# define PROMPT_PART1 "\033[32mminishell\033[0m ➜ \033[34m\033[1m"
# define PROMPT_PART2 "\033[0m $ "

typedef struct s_input
{
	char	*line;
	int		is_eof;
}			t_input;

t_status	get_command_line(t_minishell *minishell, t_input *input);

#endif
