/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:33:02 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/02 22:44:15 by hmaruyam         ###   ########.fr       */
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

char		*expand_delimiter(char *old, int *is_quoted);
char		*expand_filename(t_minishell *minishell, char *old_value,
				int *is_quoted);

char		*handle_special_word(t_minishell *minishell, char *old, int *i,
				int *is_quoted);
char		*handle_normal_word(char *old, int *i);

char		*handle_single_quote(char *old, int *i);
char		*handle_double_quote(t_minishell *minishell, char *old, int *i);

char		*expand_parameter(t_minishell *minishell, char *args, int *i);

t_status	get_args_from_lst(t_list *args_lst, t_cmd *cmd);

char		*ft_strjoin_and_free(char *s1, char *s2);
int			is_to_expand(char c);
char		*create_new_value(char *new_value, char *word);
t_status	expand_string(t_minishell *minishell, char *old_value,
				char **new_value, int *is_quoted);
void		free_pipeline_ir_after_expand(t_pipeline_ir *pipeline_ir);
void		free_cmd_ir_after_expand(t_cmd_ir *cmd_ir);
void		free_cmd_ir_after_expand_wrapper(void *cmd_ir);
void		free_args_lst_after_expand_wrapper(void *args);

void		free_cmd_wrapper(void *cmd);
void		free_cmd(t_cmd *cmd);
void		free_pipeline(t_pipeline *pipeline);

#endif
