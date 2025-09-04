/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:15:39 by aomatsud          #+#    #+#             */
/*   Updated: 2025/09/04 21:50:49 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_line_and_write_fd(char *delimiter, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			return ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

t_status	handle_heredoc(t_redir *redir)
{
	int		fd;
	char	*tmp_file;

	tmp_file = "/tmp/minishell_heredoc";
	fd = open(tmp_file, O_CREAT | O_EXCL | O_WRONLY, 0644);
	if (fd < 0)
		return (ERR_FILE);
	// TODO: delimitterのexpandを行う。double quoteでも展開しなくていいので注意。
	if (redir->value)
		read_line_and_write_fd(redir->value, fd);
	else
		return (ERR_SYNTAX);
	close(fd);
	redir->fd_hd = open(tmp_file, O_RDONLY);
	unlink(tmp_file);
	if (redir->fd_hd < 0)
		return (ERR_FILE);
	return (SUCCESS);
}

t_status	loop_heredoc(t_list *redir_lst)
{
	t_redir		*redir;
	t_status	status;

	status = SUCCESS;
	while (redir_lst)
	{
		redir = redir_lst->content;
		if (redir->type == R_HEREDOC)
			status = handle_heredoc(redir);
		else
			redir->fd_hd = -1;
		if (status != SUCCESS)
			return (status);
		redir_lst = redir_lst->next;
	}
	return (SUCCESS);
}

t_status	read_heredoc(t_list *cmd_lst)
{
	t_cmd		*cmd;
	t_status	status;

	status = SUCCESS;
	while (cmd_lst)
	{
		cmd = cmd_lst->content;
		if (cmd->redir_lst)
			status = loop_heredoc(cmd->redir_lst);
		if (status != SUCCESS)
		{
			if (status == ERR_FILE)
				assert_error(NULL, "/tmp/minishell_heredoc", ERR_FILE);
			else if (status == ERR_SYNTAX)
				assert_error(NULL, "", ERR_SYNTAX);
			else if (status == ERR_MALLOC)
				assert_error(NULL, "malloc", ERR_SYSTEM);
			return (FAILURE);
		}
		cmd_lst = cmd_lst->next;
	}
	return (SUCCESS);
}
