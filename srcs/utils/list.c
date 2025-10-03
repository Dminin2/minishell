/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:46:12 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/03 11:46:20 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	add_newlst(t_list **head, void *content)
{
	t_list *new;

	new = ft_lstnew(content);
	if (!new)
		return (ERR_SYSTEM);
	ft_lstadd_back(head, new);
	return (SUCCESS);
}
