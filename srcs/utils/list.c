/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:46:12 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/15 23:18:53 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	add_newlst(t_list **head, void *content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (!new)
		return (ERR_MALLOC);
	ft_lstadd_back(head, new);
	return (SUCCESS);
}
