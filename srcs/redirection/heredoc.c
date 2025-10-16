/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:15:39 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/17 05:10:47 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc(t_minishell *minishell, char *line)
{
	char	*new_line;
	int		start;
	char	*word;
	int		i;

	i = 0;
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
			return (NULL);
		}
		if (new_line)
			new_line = ft_strjoin_and_free(new_line, word);
		else
			new_line = word;
		if (!new_line)
		{
			free(line);
			return (NULL);
		}
	}
	free(line);
	return (new_line);
}

t_status	read_line_and_write_fd(t_minishell *minishell, char *delimiter,
		int fd, int is_quoted)
{
	char		*line;
	t_status	status;

	while (1)
	{
		line = NULL;
		if (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
			ft_putstr_fd("> ", STDERR_FILENO);
		status = gnl_and_remove_new_line(&line);
		if (g_sig == SIGINT)
		{
			free(line);
			return (SUCCESS);
		}
		if (status != SUCCESS)
			return (status);
		if (!line)
		{
			print_error_msg(delimiter, ERR_HEREDOC);
			break ;
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			return (SUCCESS);
		}
		if (line[0] != '\0' && !is_quoted)
			line = expand_heredoc(minishell, line);
		if (!line)
			return (ERR_MALLOC);
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (SUCCESS);
}

t_status	handle_heredoc(t_minishell *minishell, t_redir *redir)
{
	int			fd;
	char		*tmp_file;
	char		*delimiter;
	int			is_quoted;
	t_status	status;

	is_quoted = 0;
	delimiter = expand_delimiter(redir->value, &is_quoted);
	if (!delimiter)
		return (ERR_MALLOC);
	free(redir->value);
	redir->value = delimiter;
	tmp_file = "/tmp/minishell_heredoc";
	fd = open(tmp_file, O_CREAT | O_EXCL | O_WRONLY, 0600);
	if (fd < 0)
		return (ERR_FILE);
	status = read_line_and_write_fd(minishell, redir->value, fd, is_quoted);
	close(fd);
	if (status != SUCCESS)
	{
		unlink(tmp_file);
		return (ERR_MALLOC);
	}
	redir->fd_hd = open(tmp_file, O_RDONLY);
	unlink(tmp_file);
	if (redir->fd_hd < 0)
		return (ERR_FILE);
	return (SUCCESS);
}

t_status	loop_heredoc(t_minishell *minishell, t_list *redir_lst)
{
	t_redir		*redir;
	t_status	status;

	status = SUCCESS;
	while (redir_lst)
	{
		redir = redir_lst->content;
		if (redir->type == R_HEREDOC)
			status = handle_heredoc(minishell, redir);
		else
			redir->fd_hd = -1;
		if (status != SUCCESS)
			return (status);
		redir_lst = redir_lst->next;
	}
	return (SUCCESS);
}

t_status	read_heredoc(t_minishell *minishell, t_pipeline *pipeline)
{
	t_cmd		*cmd;
	t_status	status;
	t_list		*cur_node;

	status = SUCCESS;
	cur_node = pipeline->cmd_lst;
	if (isatty(STDIN_FILENO) && set_signal_heredoc() != SUCCESS)
	{
		minishell->last_status = assert_error_parent(pipeline, "sigaction",
				ERR_SIG);
		return (FAILURE);
	}
	while (cur_node)
	{
		cmd = cur_node->content;
		if (cmd->redir_lst)
			status = loop_heredoc(minishell, cmd->redir_lst);
		if (g_sig == SIGINT)
		{
			free_pipeline(pipeline);
			minishell->last_status = 130;
			g_sig = 0;
			status = FAILURE;
			break ;
		}
		if (status != SUCCESS)
		{
			if (status == ERR_FILE)
				minishell->last_status = assert_error_parent(pipeline,
						"/tmp/minishell_heredoc", ERR_FILE);
			else if (status == ERR_MALLOC)
				minishell->last_status = assert_error_parent(pipeline, "malloc",
						ERR_MALLOC);
			status = FAILURE;
			break ;
		}
		cur_node = cur_node->next;
	}
	if (isatty(STDIN_FILENO) && set_signal_interactive() != SUCCESS)
	{
		if (status == SUCCESS)
			minishell->last_status = assert_error_parent(pipeline, "sigaction",
					ERR_SIG);
		else
			minishell->last_status = assert_error_parent(NULL, "sigaction",
					ERR_SIG);
		minishell->should_exit = 1;
		return (FAILURE);
	}
	return (status);
}
