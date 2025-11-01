/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:05:45 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/01 09:11:54 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_save(char **save)
{
	if (!*save)
		return (NULL);
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
	static char	*save[OPEN_MAX];

	if (BUFFER_SIZE <= 0)
		return (free_save(&save[fd]));
	if (fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_save(&save[fd]));
	if (!save[fd])
	{
		save[fd] = ft_strdup("");
		if (!save[fd])
			return (free(buf), NULL);
	}
	save[fd] = read_and_save(fd, buf, save[fd]);
	if (!save[fd] || !*(save[fd]))
		return (free_save(&save[fd]));
	line = put_line(save[fd]);
	if (!line)
		return (free_save(&save[fd]));
	save[fd] = remove_line(save[fd]);
	return (line);
}
