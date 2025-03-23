#include "../include/minishell.h"

static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGQUIT)
	{
		printf("%s%s", "minishell: ", rl_line_buffer);
		rl_redisplay();
	}
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	(void)context;
	(void)info;
}

void	setup_term(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	init_sigaction(void)
{
	struct sigaction	sa;

	setup_term();
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
