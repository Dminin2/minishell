/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:49:03 by aomatsud          #+#    #+#             */
/*   Updated: 2025/05/11 02:38:25 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_save(char **save)
{
	free(*save);
	*save = NULL;
	return (NULL);
}

static char	*put_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(line, save, i + 1);
	return (line);
}

static char	*remove_line(char *save)
{
	int		i;
	char	*new_save;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	new_save = ft_strdup(&save[i]);
	free(save);
	if (!new_save || !*new_save)
		return (free_save(&new_save));
	return (new_save);
}

static char	*read_and_save(int fd, char *buf, char *save)
{
	int	read_bytes;

	while (!ft_strchr(save, '\n'))
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(buf);
			return (free_save(&save));
		}
		if (read_bytes == 0)
			break ;
		buf[read_bytes] = '\0';
		save = ft_strjoin_free(save, buf);
		if (!save)
		{
			free(buf);
			return (NULL);
		}
	}
	free(buf);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*save = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_save(&save));
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_save(&save));
	if (!save)
	{
		save = ft_strdup("");
		if (!save)
			return (free(buf), NULL);
	}
	save = read_and_save(fd, buf, save);
	if (!save || !*save)
		return (free_save(&save));
	line = put_line(save);
	if (!line)
		return (free_save(&save));
	save = remove_line(save);
	return (line);
}
