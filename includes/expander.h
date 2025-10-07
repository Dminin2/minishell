/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:33:02 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/07 15:14:44 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "common.h"
# include "parser.h"
# include "redirection.h"
# include <stdlib.h>

typedef struct s_cmd
{
	char	**args;
	char	*path;
	t_list	*redir_lst;
}			t_cmd;

typedef struct s_pipeline
{
	t_list	*cmd_lst;
	int		n;
	int		**pipes;
}			t_pipeline;

t_pipeline	*expand(t_minishell *minishell, t_pipeline_ir *pipeline_ir);

t_status	expand_args_lst(t_minishell *minishell, t_list *args_lst);
t_status	expand_redir_lst(t_minishell *minishell, t_list *redir_lst,
				t_redir **redir_err);

char		*handle_special_word(t_minishell *minishell, char *old, int *i,
				int *is_quoted);
char		*handle_normal_word(char *old, int *i);

char		*handle_single_quote(char *old, int *i);
char		*handle_double_quote(t_minishell *minishell, char *old, int *i);

char		*expand_parameter(t_minishell *minishell, char *args, int *i);

t_status	get_args_from_lst(t_list *args_lst, t_cmd *cmd);

char		*ft_strjoin_and_free(char *s1, char *s2);
int			is_to_expand(char c);
int			is_valid_key_first_char(char c);
int			is_valid_key_char(char c);

void		free_pipeline_ir_after_expand(t_pipeline_ir *pipeline_ir);
void		free_cmd_ir_after_expand(t_cmd_ir *cmd_ir);
void		free_cmd_ir_after_expand_wrapper(void *cmd_ir);
void		free_args_lst_after_expand_wrapper(void *args);

void		free_cmd_wrapper(void *cmd);
void		free_cmd(t_cmd *cmd);
void		free_pipeline(t_pipeline *pipeline);

#endif
