/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:41:27 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/06 15:25:22 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_builtin_malloc_error(t_minishell *minishell)
{
	print_error_msg("malloc", ERR_MALLOC);
	minishell->should_exit = 1;
	minishell->last_status = 2;
}
