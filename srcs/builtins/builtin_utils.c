/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:41:27 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/06 13:34:09 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_error(t_minishell *minishell, char *msg, t_status status)
{
	print_error_msg(msg, status);
	if (status == ERR_MALLOC)
		minishell->should_exit = 1;
	return (1);
}
