/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:37:20 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/02 09:15:19 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "common.h"
# include "libft.h"
# include <stdlib.h>

typedef struct s_cmd_ir
{
	t_list		*args_lst;
	t_list		*redir_lst;
}				t_cmd_ir;

typedef struct s_pipeline_ir
{
	t_list		*cmd_ir_lst;
	int			n;
}				t_pipeline_ir;

t_pipeline_ir	*parse(t_list *tok_lst);
void			handle_error(t_list *tok_lst, t_list *head, t_status status);
t_status		get_redirection(t_list **tok_lst, t_cmd_ir *cmd_ir);
t_status		get_simple_command(t_list **tok_lst, t_cmd_ir *cmd_ir);

t_status		add_newlst(t_list **head, void *content);

#endif
