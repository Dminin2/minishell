/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:33:02 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/03 01:16:18 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "common.h"
# include "parser.h"
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

char		*handle_single_quote(char *old, int *i);
char		*handle_double_quote(t_minishell *minishell, char *old, int *i);

char		*expand_parameter(t_minishell *minishell, char *args, int *i);

t_status	get_args_from_lst(t_list *args_lst, t_cmd *cmd);

char		*ft_strjoin_and_free(char *s1, char *s2);
int			is_to_expand(char c);
int			is_valid_key_first_char(char c);
int			is_valid_key_char(char c);

void		free_cmd_wrapper(void *cmd);
void		free_cmd(t_cmd *cmd);
void		free_pipes(int **pipes, int n);
void		free_pipeline(t_pipeline *pipeline);

#endif
