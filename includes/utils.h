/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:18:32 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/03 11:22:46 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "common.h"
# include "env.h"
# include "expander.h"
# include "lexer.h"
# include "parser.h"
# include "redirection.h"
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

void	free_args(char **args);

void	free_token_wrapper(void *tok);
void	free_token(t_token *tok);

void	free_redir(t_redir *redir);
void	free_cmd(t_cmd *cmd);
void	free_cmd_wrapper(void *cmd);
void	free_pipes(int **pipes, int n);
void	free_pipeline(t_pipeline *pipeline);

void	free_str_wrapper(void *str);
void	free_str(char *str);
void	free_cmd_ir_wrapper(void *cmd_ir);
void	free_cmd_ir(t_cmd_ir *cmd_ir);
void	free_pipeline_ir(t_pipeline_ir *pipeline_ir);
void	free_pipeline_ir_after_expand(t_pipeline_ir *pipeline_ir);

void	free_env_wrapper(void *env);
void	free_env(t_env *env);

void	close_heredoc(t_list *cmd_lst);
void	close_pipes(int **pipes, int n);

void	print_error_msg(char *context, t_status status);
void	assert_error_lst(t_list *lst, char *context, t_status status,
			void (*del)(void *));
void	assert_error_parent(t_pipeline *pipeline, char *context,
			t_status status);
void	exit_error(t_pipeline *pipeline, char *context, t_status status,
			int exit_status);

#endif
