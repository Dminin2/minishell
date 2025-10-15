/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:17:56 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/15 21:57:31 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>

t_status	get_command_line(char **line);

#endif
