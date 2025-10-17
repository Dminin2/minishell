/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 02:46:49 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/17 14:31:50 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

void	sigint_handler_in_readline(int signo)
{
	(void)signo;
	g_sig = SIGINT;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler_in_heredoc(int signo)
{
	(void)signo;
	g_sig = SIGINT;
	write(STDERR_FILENO, "\n", 1);
}

t_status	set_action(int sig, void (*handler)(int))
{
	struct sigaction	sig_act;

	sig_act.sa_handler = handler;
	sig_act.sa_flags = 0;
	sigemptyset(&sig_act.sa_mask);
	if (sigaction(sig, &sig_act, NULL) == -1)
		return (ERR_SIG);
	return (SUCCESS);
}

t_status	set_signal_interactive(void)
{
	if (set_action(SIGINT, sigint_handler_in_readline) == ERR_SIG)
		return (ERR_SIG);
	if (set_action(SIGQUIT, SIG_IGN) == ERR_SIG)
		return (ERR_SIG);
	return (SUCCESS);
}

t_status	set_signal_noninteractive(void)
{
	if (set_action(SIGINT, SIG_DFL) == ERR_SIG)
		return (ERR_SIG);
	if (set_action(SIGQUIT, SIG_IGN) == ERR_SIG)
		return (ERR_SIG);
	return (SUCCESS);
}

t_status	set_signal_heredoc(void)
{
	if (set_action(SIGINT, sigint_handler_in_heredoc) == ERR_SIG)
		return (ERR_SIG);
	if (set_action(SIGQUIT, SIG_IGN) == ERR_SIG)
		return (ERR_SIG);
	return (SUCCESS);
}

t_status	set_signal_default(void)
{
	if (set_action(SIGINT, SIG_DFL) == ERR_SIG)
		return (ERR_SIG);
	if (set_action(SIGQUIT, SIG_DFL) == ERR_SIG)
		return (ERR_SIG);
	return (SUCCESS);
}

t_status	set_signal_wait_child(void)
{
	if (set_action(SIGINT, SIG_IGN) == ERR_SIG)
		return (ERR_SIG);
	if (set_action(SIGQUIT, SIG_IGN) == ERR_SIG)
		return (ERR_SIG);
	return (SUCCESS);
}
