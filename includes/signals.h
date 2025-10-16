/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomatsud <aomatsud@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 02:45:41 by aomatsud          #+#    #+#             */
/*   Updated: 2025/10/17 03:51:11 by aomatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "common.h"
# include <signal.h>

extern volatile sig_atomic_t	g_sig;

t_status						set_signal_interactive(void);
t_status						set_signal_noninteractive(void);

#endif
