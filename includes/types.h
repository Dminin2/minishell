/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:21:17 by aomatsud          #+#    #+#             */
/*   Updated: 2025/08/18 20:44:57 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_cmd
{
	char	*path;
	char	**args;
}			t_cmd;

typedef enum e_status
{
	SUCCESS,
	ERR_SYSTEM
}			t_status;

#endif
