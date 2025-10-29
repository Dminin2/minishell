/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:59:45 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/29 22:06:31 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "env.h"
# include "expander.h"
# include "lexer.h"
# include "parser.h"
# include "redirection.h"
# include <stdio.h>

void	print_token(t_list *head, int fd);
void	print_pipeline_ir(t_pipeline_ir *pipeline_ir, int fd);
void	print_pipeline(t_pipeline *pipeline, int fd);
void	print_redir_lst(t_list *head, int fd);
void	print_env_lst(t_list *env_lst, int fd);
void	print_status(int status, int fd);
void	print_input(t_input *input, int fd);

#endif
