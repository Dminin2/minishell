/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:10:05 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/31 14:07:17 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*convert_to_hex(char *buf)
{
	char				new_buf[17];
	static const char	hex[16] = "0123456789abcdef";
	int					i;

	i = 0;
	while (i < 8)
	{
		new_buf[2 * i] = hex[(unsigned char)buf[i] / 16];
		new_buf[2 * i + 1] = hex[(unsigned char)buf[i] % 16];
		i++;
	}
	new_buf[2 * i] = '\0';
	return (ft_strdup(new_buf));
}

t_status	create_hd_filename(char **tmp_file)
{
	int		random_fd;
	int		n;
	char	*hex_id;
	char	buf[8];

	random_fd = open("/dev/urandom", O_RDONLY);
	if (random_fd < 0)
		return (ERR_HD_FILE);
	n = read(random_fd, buf, sizeof(buf));
	close(random_fd);
	if (n < 8)
		return (ERR_HD_FILE);
	hex_id = convert_to_hex(buf);
	if (!hex_id)
		return (ERR_MALLOC);
	*tmp_file = ft_strjoin("/tmp/minishell_heredoc_", hex_id);
	free(hex_id);
	if (!(*tmp_file))
		return (ERR_MALLOC);
	return (SUCCESS);
}
