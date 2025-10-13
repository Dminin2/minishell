/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:17:01 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/10/10 10:47:44 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_escape_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '`' || str[i] == '$' || str[i] == '\\')
			ft_putchar_fd('\\', STDOUT_FILENO);
		ft_putchar_fd(str[i], STDOUT_FILENO);
		i++;
	}
}

void	bubble_sort_env_array(t_list **env_array, size_t env_count)
{
	size_t	i;
	size_t	j;
	t_list	*tmp;
	char	*key1;
	char	*key2;

	i = 0;
	while (i < env_count - 1)
	{
		j = 0;
		while (j < env_count - i - 1)
		{
			key1 = ((t_env *)(env_array[j]->content))->key;
			key2 = ((t_env *)(env_array[j + 1]->content))->key;
			if (ft_strcmp(key1, key2) > 0)
			{
				tmp = env_array[j];
				env_array[j] = env_array[j + 1];
				env_array[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

bool	is_valid_identifier(char *key)
{
	int	i;

	if (!is_valid_key_first_char(key[0]))
		return (false);
	i = 1;
	while (key[i])
	{
		if (!is_valid_key_char(key[i]))
			return (false);
		i++;
	}
	return (true);
}
