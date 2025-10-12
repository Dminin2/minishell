/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 23:15:17 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/12 16:23:52 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_minishell *minishell, char **args)
{
	if (!args[1])
		return (handle_no_args(minishell));
	else
		return (handle_args(minishell, args));
}
