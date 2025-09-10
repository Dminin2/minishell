/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:18:32 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/09 18:58:22 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

void	free_args(char **args);
void	free_token_wrapper(void *tok);
void	free_token(t_token *tok);
void	free_redir(t_redir *redir);
void	free_cmd(t_cmd *cmd);
void	free_cmd_wrapper(void *cmd);
void	free_pipes(int **pipes, int n);
void	free_pipeline(t_pipeline *pipeline);

void	close_heredoc(t_list *cmd_lst);
void	close_pipes(int **pipes, int n);

void	print_error_msg(char *context, t_status status);
void	assert_error(t_list *lst, char *context, t_status status);
void	assert_error_parser(t_list *lst, char *context, t_status status);
void	assert_error_parent(t_pipeline *pipeline, char *context,
			t_status status);
void	exit_error(t_pipeline *pipeline, char *context, t_status status,
			int exit_status);

#endif
