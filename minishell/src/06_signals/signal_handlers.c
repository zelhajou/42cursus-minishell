/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:20:26 by beddinao          #+#    #+#             */
/*   Updated: 2024/03/07 09:04:42 by beddinao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_signal_handlers(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	child_ctrl_c(int sig_num)
{
	if (sig_num == 2)
		g_thing = 130;
	else
	{
		ft_putstr_fd("minishell: quit signal detected\n", 1);
		g_thing = 131;
	}
	write(1, "\n", 1);
}

void	handle_ctrl_c(int a)
{
	(void)a;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}
