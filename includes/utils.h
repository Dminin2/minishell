/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:18:32 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/29 21:44:43 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "common.h"
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_normalize_status
{
	NORMALIZE_SUCCESS,
	NORMALIZE_STAT_FAILED,
	NORMALIZE_MALLOC_ERROR
}							t_normalize_status;

typedef enum e_blt_error	t_blt_error;
typedef struct s_pipeline	t_pipeline;
typedef struct s_input		t_input;

void						free_args(char **args);
void						free_str_wrapper(void *str);
void						free_str(char *str);

void						close_heredoc(t_list *cmd_lst);
void						close_pipes(int **pipes, int n);

t_status					add_newlst(t_list **head, void *content);

int							ft_strcmp(char *s1, char *s2);
int							is_blank(char c);
int							is_whitespace(char c);

t_status					gnl_and_remove_new_line(t_input *input);

void						print_error_msg(char *context, t_status status);
void						print_error_msg_builtin(char *cmd, char *context,
								t_blt_error error);
int							error_lst(t_list *lst, char *context,
								t_status status, void (*del)(void *));
int							error_parent(t_pipeline *pipeline, char *context,
								t_status status);
void						exit_error(t_minishell *minishell,
								t_pipeline *pipeline, char *context,
								t_status status);
void						exit_success(t_minishell *minishell,
								t_pipeline *pipeline);

int							is_pwd_valid(char *pwd_path);

t_normalize_status			normalize_path(const char *abs_path, char **result);

#endif
