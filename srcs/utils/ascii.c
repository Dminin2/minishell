/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 23:38:33 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/27 23:41:23 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*convert_whitespace_to_ascii(char *old)
{
	static char	*ws_char[] = {"$'\\a'", "$'\\b'", "$'\\t'", "$'\\n'", "$'\\v'",
			"$'\\f'", "$'\\r'"};
	char		*new;
	char		*tmp;
	int			i;
	int			start;

	i = 0;
	new = NULL;
	while (old[i])
	{
		if (is_non_space_whitespace(old[i]))
		{
			tmp = ft_strdup(ws_char[old[i] - 7]);
			i++;
		}
		else
		{
			start = i;
			while (old[i] && !is_non_space_whitespace(old[i]))
				i++;
			tmp = ft_substr(old, start, i - start);
		}
		if (new)
			new = ft_strjoin_and_free(new, tmp);
		else
			new = tmp;
		if (!new)
			return (NULL);
	}
	return (new);
}
