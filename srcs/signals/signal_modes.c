/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_modes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 19:08:23 by hmaruyam          #+#    #+#             */
/*   Updated: 2025/11/02 19:08:29 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
