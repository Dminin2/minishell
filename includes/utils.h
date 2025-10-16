/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:18:32 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/14 15:34:59 by aomatsud         ###   ########.fr       */
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

#endif
