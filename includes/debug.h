/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 20:59:45 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/30 13:30:52 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "env.h"
# include "expander.h"
# include "lexer.h"
# include "redirection.h"

void	print_token(t_list *head);
void	print_pipeline_ir(t_pipeline_ir *pipeline_ir);
void	print_pipeline(t_pipeline *pipeline);
void	print_redir_lst(t_list *head);
void	print_env_lst(t_list *env_lst);
void	print_status(int status);

#endif
