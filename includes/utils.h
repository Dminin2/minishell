/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:18:32 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/06 13:35:06 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "common.h"
# include <errno.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define CMD_ERR "command not found"
# define VLD_ERR "No such file or directory"
# define SYN_ERR "syntax error near unexpected token"
# define HD_ERR "warning: here-document delimited by end-of-file (wanted"
# define QUOTE_ERR "syntax error: unexpected"
# define AMB_ERR "ambiguous redirect"

# define HOME_ERR "HOME not set"
# define OLDPWD_ERR "OLDPWD not set"
# define ARG_ERR "too many arguments"

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
char						*ft_strjoin_and_free(char *s1, char *s2);

t_status					gnl_and_remove_new_line(t_input *input);

void						print_error_msg(char *context, t_status status);
void						print_error_msg_builtin(char *cmd, char *context,
								t_blt_error error);
int							error_lst(t_list *lst, char *context,
								t_status status, void (*del)(void *));
void						error_parent(t_minishell *minishell,
								t_pipeline *pipeline, char *context,
								t_status status);
void						exit_error(t_minishell *minishell,
								t_pipeline *pipeline, char *context,
								t_status status);
void						exit_success(t_minishell *minishell,
								t_pipeline *pipeline);
int							get_exit_status(t_status status);

int							is_pwd_valid(char *pwd_path);

#endif
