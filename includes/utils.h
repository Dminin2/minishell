/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:18:32 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/16 18:59:47 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "common.h"
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_blt_error	t_blt_error;
typedef struct s_pipeline	t_pipeline;

void						free_args(char **args);
void						free_str_wrapper(void *str);
void						free_str(char *str);

void						close_heredoc(t_list *cmd_lst);
void						close_pipes(int **pipes, int n);

t_status					add_newlst(t_list **head, void *content);

int							ft_strcmp(char *s1, char *s2);
int							is_blank(char c);
int							is_whitespace(char c);

t_status					gnl_and_remove_new_line(char **line);

void						print_error_msg(char *context, t_status status);
void						print_error_msg_builtin(char *cmd, char *context,
								t_blt_error error);
int							error_lst(t_list *lst, char *context,
								t_status status, void (*del)(void *));
int							error_parent(t_pipeline *pipeline,
								char *context, t_status status);
void						exit_error(t_minishell *minishell,
								t_pipeline *pipeline, char *context,
								t_status status);
void						exit_success(t_minishell *minishell,
								t_pipeline *pipeline);

int							is_pwd_valid(char *pwd_path);

#endif
