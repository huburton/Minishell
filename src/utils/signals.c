/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:40:16 by phiascha          #+#    #+#             */
/*   Updated: 2025/06/17 15:18:18 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_signal_status = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	g_signal_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_handler2(int sig)
{
	(void)sig;
	g_signal_status = 130;
	write(STDOUT_FILENO, "\n", 1);
}

void	sigquit_handler(int sig)
{
	(void)sig;
	g_signal_status = 131;
	print_error("Quit (core dumped)\n");
}

void	setup_signals2(void)
{
	signal(SIGINT, sigint_handler2);
	signal(SIGQUIT, sigquit_handler);
}
