/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaruyam <hmaruyam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 02:45:41 by aomatsud          #+#    #+#             */
/*   Updated: 2025/11/02 19:08:32 by hmaruyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "common.h"
# include <signal.h>

extern volatile sig_atomic_t	g_sig;

void							set_signal_interactive(void);
void							set_signal_noninteractive(void);
void							set_signal_heredoc(void);
void							set_signal_default(void);
void							set_signal_wait_child(void);

#endif
