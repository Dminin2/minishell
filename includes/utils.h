/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:18:32 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/03 11:46:30 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "common.h"
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

void		free_args(char **args);
void		free_str_wrapper(void *str);
void		free_str(char *str);

void		close_heredoc(t_list *cmd_lst);
void		close_pipes(int **pipes, int n);

void		print_error_msg(char *context, t_status status);
void		assert_error(t_list *lst, char *context, t_status status);
void		assert_error_parser(t_list *lst, char *context, t_status status);
void		assert_error_parent(t_pipeline *pipeline, char *context,
				t_status status);
void		assert_error_env_init(t_list *env_lst, char *context,
				t_status status);
void		assert_error_expander(t_list *cmd_lst, char *context,
				t_status status);
void		exit_error(t_pipeline *pipeline, char *context, t_status status,
				int exit_status);

t_status	add_newlst(t_list **head, void *content);

#endif
