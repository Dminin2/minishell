/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:15:39 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/31 14:45:39 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	expand_heredoc(t_minishell *minishell, int old_fd, int new_fd)
{
	char	*new_line;
	int		start;
	char	*word;
	int		i;
	char	*line;

	while (1)
	{
		i = 0;
		line = get_next_line(old_fd);
		if (!line)
			break ;
		new_line = NULL;
		while (line[i])
		{
			if (line[i] == '$')
				word = expand_parameter(minishell, line, &i);
			else
			{
				start = i;
				while (line[i] && line[i] != '$')
					i++;
				word = ft_substr(line, start, i - start);
			}
			if (!word)
			{
				free(line);
				free(new_line);
				return (ERR_MALLOC);
			}
			if (new_line)
				new_line = ft_strjoin_and_free(new_line, word);
			else
				new_line = word;
			if (!new_line)
			{
				free(line);
				return (ERR_MALLOC);
			}
		}
		ft_putstr_fd(new_line, new_fd);
		free(line);
		free(new_line);
	}
	return (SUCCESS);
}

t_status	read_line_and_write_fd(char *delimiter, int fd)
{
	t_status	status;
	t_input		input;

	while (1)
	{
		input.line = NULL;
		input.is_eof = 0;
		if (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
			ft_putstr_fd("> ", STDERR_FILENO);
		status = gnl_and_remove_new_line(&input);
		if (g_sig == SIGINT)
		{
			free(input.line);
			return (RCV_SIGINT);
		}
		if (status != SUCCESS)
			return (status);
		if (!(input.line))
		{
			print_error_msg(delimiter, ERR_HEREDOC);
			break ;
		}
		if (ft_strncmp(input.line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(input.line);
			return (SUCCESS);
		}
		ft_putendl_fd(input.line, fd);
		free(input.line);
	}
	return (SUCCESS);
}

t_status	read_heredoc(t_redir *redir)
{
	int fd;
	char *tmp_file;
	char *delimiter;
	t_status status;

	delimiter = expand_delimiter(redir->value, &(redir->delimiter_is_quoted));
	if (!delimiter)
		return (ERR_MALLOC);
	free(redir->value);
	redir->value = delimiter;
	status = create_hd_filename(&tmp_file);
	if (status != SUCCESS)
		return (status);
	fd = open(tmp_file, O_CREAT | O_EXCL | O_WRONLY, 0600);
	if (fd < 0)
	{
		free(tmp_file);
		return (ERR_FILE);
	}
	if (isatty(STDIN_FILENO))
		set_signal_heredoc();
	status = read_line_and_write_fd(redir->value, fd);
	if (isatty(STDIN_FILENO))
		set_signal_interactive();
	close(fd);
	if (status != SUCCESS)
	{
		unlink(tmp_file);
		free(tmp_file);
		return (status);
	}
	redir->fd_hd = open(tmp_file, O_RDONLY);
	unlink(tmp_file);
	free(tmp_file);
	if (redir->fd_hd < 0)
		return (ERR_HD_FILE);
	return (SUCCESS);
}
