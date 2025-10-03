/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:03:44 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/03 01:17:02 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "common.h"
# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_HEREDOC,
	R_APPEND
}					t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*value;
	int				fd_hd;
}					t_redir;

typedef struct s_redir_err
{
	t_status		status;
	t_redir			*redir_err;
}					t_redir_err;

void				redirect(t_list *redir_lst, t_redir_err *err);
t_status			read_heredoc(t_list *cmd_lst);

void				free_redir_wrapper(void *redir);
void				free_redir(t_redir *redir);

#endif
