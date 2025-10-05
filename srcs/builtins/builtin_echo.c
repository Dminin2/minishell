/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:10:56 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/06 01:48:04 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_option(char *arg)
{
	int	i;

	if (strncmp(arg, "-n", 2) != 0)
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
int	builtin_echo(char **args)
{
	bool	n_option;
	int		i;

	i = 1;
	n_option = false;
	while (args[i] && is_valid_n_option(args[i]))
	{
		n_option = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_option)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
