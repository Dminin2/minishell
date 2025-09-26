/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:33:54 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/26 21:34:36 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_list *args_lst)
{
	int	n;

	n = 0;
	while (args_lst)
	{
		n++;
		args_lst = args_lst->next;
	}
	return (n);
}

t_status	get_args_from_lst(t_list *args_lst, t_cmd *cmd)
{
	char	**new_args;
	char	*old;
	int		n;
	int		i;

	n = count_args(args_lst);
	new_args = ft_calloc(sizeof(char *), n + 1);
	if (!new_args)
		return (ERR_MALLOC);
	i = 0;
	while (args_lst)
	{
		old = args_lst->content;
		new_args[i] = old;
		i++;
		args_lst = args_lst->next;
	}
	cmd->args = new_args;
	return (SUCCESS);
}
