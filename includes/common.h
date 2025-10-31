/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:29:06 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/31 15:24:45 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "ft_dprintf.h"
# include "get_next_line.h"
# include "libft.h"

typedef enum e_status
{
	SUCCESS,
	ERR_SYNTAX,
	ERR_CMD_NOT_FOUND,
	ERR_NOT_VALID_PATH,
	ERR_ISDIR,
	ERR_EACCES,
	ERR_ENOENT,
	ERR_ENOTDIR,
	ERR_EXECVE_OTHER,
	ERR_FILE,
	ERR_AMB_REDIR,
	ERR_DUP,
	ERR_MALLOC,
	ERR_PIPE,
	ERR_FORK,
	ERR_WAITPID,
	ERR_HEREDOC,
	ERR_QUOTE,
	ERR_NOKEY,
	RCV_SIGINT,
	ERR_ERRNO,
}			t_status;

typedef struct s_minishell
{
	t_list	*env_lst;
	char	*cwd;
	int		last_status;
	int		should_exit;
}			t_minishell;

#endif
