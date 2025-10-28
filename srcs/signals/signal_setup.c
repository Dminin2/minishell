/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 02:46:49 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/26 12:51:37 by aomatsud         ###   ########.fr       */
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

void	set_action(int sig, void (*handler)(int))
{
	struct sigaction	sig_act;

	sig_act.sa_handler = handler;
	sig_act.sa_flags = 0;
	sigemptyset(&sig_act.sa_mask);
	sigaction(sig, &sig_act, NULL);
}

void	set_signal_interactive(void)
{
	set_action(SIGINT, sigint_handler_in_readline);
	set_action(SIGQUIT, SIG_IGN);
}

void	set_signal_noninteractive(void)
{
	set_action(SIGINT, SIG_DFL);
	set_action(SIGQUIT, SIG_IGN);
}

void	set_signal_heredoc(void)
{
	set_action(SIGINT, sigint_handler_in_heredoc);
	set_action(SIGQUIT, SIG_IGN);
}

void	set_signal_default(void)
{
	set_action(SIGINT, SIG_DFL);
	set_action(SIGQUIT, SIG_DFL);
}

void	set_signal_wait_child(void)
{
	set_action(SIGINT, SIG_IGN);
	set_action(SIGQUIT, SIG_IGN);
}
