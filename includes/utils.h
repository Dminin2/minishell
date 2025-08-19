/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:18:32 by aomatsud          #+#    #+#             */
/*   Updated: 2025/08/18 09:36:51 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

void	free_args(char **args);
void	free_cmd(t_cmd *cmd);

void	exit_error(t_cmd *cmd, char *context, t_status status, int exit_status);

#endif
