/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list_to_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:33:54 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/04 12:01:50 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_list *args_lst)
{
	int	n;

	n = 0;
	while (args_lst)
	{
		if (args_lst->content)
			n++;
		args_lst = args_lst->next;
	}
	return (n);
}

t_status	convert_list_to_array(t_list *args_lst, t_cmd *cmd)
{
	char	**new_args;
	int		n;
	int		i;

	n = count_args(args_lst);
	new_args = ft_calloc(sizeof(char *), n + 1);
	if (!new_args)
		return (ERR_MALLOC);
	i = 0;
	while (args_lst)
	{
		if (args_lst->content)
		{
			new_args[i] = args_lst->content;
			args_lst->content = NULL;
			i++;
		}
		args_lst = args_lst->next;
	}
	cmd->args = new_args;
	return (SUCCESS);
}
