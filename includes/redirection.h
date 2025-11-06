/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:03:44 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/05 18:35:15 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "common.h"
# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
typedef struct s_pipeline	t_pipeline;

# define HD_FILE_ERR "cannot create temp file for here-document"

typedef enum e_redir_type
{
	R_IN,
	R_OUT,
	R_HEREDOC,
	R_APPEND
}							t_redir_type;

typedef struct s_redir
{
	t_redir_type			type;
	char					*value;
	int						fd_hd;
	int						delimiter_is_quoted;
}							t_redir;

typedef struct s_redir_err
{
	t_status				status;
	t_redir					*redir_err;
}							t_redir_err;

void						redirect(t_minishell *minishell, t_list *redir_lst,
								t_redir_err *err);
t_status					create_hd_filename(char **fname_hd);

void						redir_append(t_redir *redir, t_redir_err *err);
void						redir_in(t_redir *redir, t_redir_err *err);
void						redir_out(t_redir *redir, t_redir_err *err);

t_status					read_heredoc(t_redir *redir);
t_status					expand_heredoc(t_minishell *minishell, int old_fd,
								int new_fd);

void						free_redir_wrapper(void *redir);
void						free_redir(t_redir *redir);

#endif
