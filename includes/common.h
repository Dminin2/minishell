/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:29:06 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/15 23:20:53 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "libft.h"

typedef enum e_status
{
	SUCCESS,
	FAILURE,
	ERR_SYNTAX,
	ERR_CMD_NOT_FOUND,
	ERR_NOT_VALID_PATH,
	ERR_ISDIR,
	ERR_FILE,
	ERR_AMB_REDIR,
	ERR_DUP,
	ERR_MALLOC,
	ERR_PIPE,
	ERR_FORK,
	ERR_WAITPID,
	ERR_ERRNO
}			t_status;

typedef struct s_minishell
{
	t_list	*env_lst;
	int		last_status;
	int		should_exit;
}			t_minishell;

#endif
