/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 01:11:45 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/02 09:18:56 by hmaruyam         ###   ########.fr       */
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

void		execute(t_pipeline *pipeline, int pos, char **envp);
void		child_process(t_pipeline *pipeline, char **envp);

t_cmd		*get_cmd_from_lst(t_list *head, int target);

t_status	resolve_command_path(t_cmd *cmd, char **envp);

t_status	create_pipes(t_pipeline *pipeline);
t_status	pipe_pipes(int **pipes, int n);
t_status	pipe_duplicate(t_pipeline *pipeline, int pos);

#endif
