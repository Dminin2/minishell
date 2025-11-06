/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 12:31:17 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/06 11:32:24 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_to_expand(char c)
{
	if (c == '\'' || c == '\"' || c == '$')
		return (1);
	else
		return (0);
}

char	*create_new_value(char *new_value, char *word)
{
	if (new_value)
		return (ft_strjoin_and_free(new_value, word));
	else
		return (word);
}
