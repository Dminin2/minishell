/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 01:11:45 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/14 13:23:31 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "expander.h"
# include <errno.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_command_type
{
	NO_CMD,
	EXTERNAL,
	BLT_ECHO,
	BLT_CD,
	BLT_PWD,
	BLT_EXPORT,
	BLT_UNSET,
	BLT_ENV,
	BLT_EXIT
}				t_command_type;

void			execute(t_minishell *minishell, t_pipeline *pipeline);

void			handle_redir_err(t_minishell *minishell, t_pipeline *pipeline,
					t_redir_err err);
void			run_in_child(t_minishell *minishell, t_pipeline *pipeline,
					int pos);
void			child_process(t_minishell *minishell, t_pipeline *pipeline);

void			run_builtin_in_parent(t_minishell *minishell,
					t_pipeline *pipeline, t_command_type type);

t_cmd			*get_cmd_from_lst(t_list *head, int target);

t_command_type	scan_command_type(t_cmd *cmd);
void			execute_builtin(t_minishell *minishell, t_cmd *cmd,
					t_command_type type);

char			**split_path_value(char *path_value);
t_status		resolve_command_path(t_cmd *cmd, t_list *env_lst);

t_status		create_pipes(t_pipeline *pipeline);
t_status		pipe_pipes(int **pipes, int n);
t_status		pipe_duplicate(t_pipeline *pipeline, int pos);

t_status		save_stdio_fd(t_list *redir_lst, int *saved);
t_status		restore_stdio_fd(int *saved);

void			free_pipes(int **pipes, int n);

#endif
