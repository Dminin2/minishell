/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:37:20 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/02 17:41:55 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

t_pipeline	*parse(t_list *tok_lst);
void		handle_error(t_list *tok_lst, t_list *head, t_status status);
t_status	get_redirection(t_list **tok_lst, t_cmd *cmd);
t_status	get_simple_command(t_list **tok_lst, t_cmd *cmd);

t_status	add_newlst(t_list **head, void *content);

#endif
