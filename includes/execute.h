/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 01:11:45 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/04 20:18:04 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "types.h"

void		execute(t_pipeline *pipeline, char **envp);
void		child_process(t_pipeline *pipeline, char **envp);

t_status	resolve_command_path(t_cmd *cmd, char **envp);

#endif
