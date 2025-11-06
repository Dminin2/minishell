/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:57:17 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/05 18:08:04 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_next_word(t_minishell *minishell, char *line, int *i)
{
	int	start;

	if (line[*i] == '$')
		return (expand_parameter(minishell, line, i));
	start = *i;
	while (line[*i] && line[*i] != '$')
		(*i)++;
	return (ft_substr(line, start, *i - start));
}

static char	*expand_line(t_minishell *minishell, char *line)
{
	int		i;
	char	*new_line;
	char	*word;

	i = 0;
	new_line = NULL;
	while (line[i])
	{
		word = get_next_word(minishell, line, &i);
		if (!word)
		{
			free(new_line);
			return (NULL);
		}
		new_line = create_new_value(new_line, word);
		if (!new_line)
			return (NULL);
	}
	return (new_line);
}

t_status	expand_heredoc(t_minishell *minishell, int old_fd, int new_fd)
{
	char	*new_line;
	char	*line;

	while (1)
	{
		line = get_next_line(old_fd);
		if (!line)
			break ;
		new_line = expand_line(minishell, line);
		free(line);
		if (!new_line)
			return (ERR_MALLOC);
		ft_putstr_fd(new_line, new_fd);
		free(new_line);
	}
	return (SUCCESS);
}
