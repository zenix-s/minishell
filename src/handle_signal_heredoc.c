/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/02/11 23:43:21 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_heredoc_signal(int sig)
{
	char	c;

	if (sig == SIGINT)
	{
		c = '\n';
		ioctl(STDIN_FILENO, TIOCSTI, &c);
		g_exit_status = 330;
	}
}

void	set_signal_for_heredoc(void)
{
	struct sigaction	sa;
	struct sigaction	ignore;

	sa.sa_handler = handle_heredoc_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	ignore.sa_handler = SIG_IGN;
	ignore.sa_flags = 0;
	sigemptyset(&ignore.sa_mask);
	sigaction(SIGQUIT, &ignore, NULL);
}
