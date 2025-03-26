/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:53:18 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/23 13:53:22 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	head(void)
{
	printf("\033[0;32m");
	printf("         .__         .__         .__             .__   .__   \n");
	printf("  _____  |__|  ____  |__|  ______|  |__    ____  |  |  |  |  \n");
	printf(" /     \\ |  | /    \\ |  | /  ___/");
	printf("|  |  \\ _/ __ \\ |  |  |  |  \n");
	printf("|  Y Y  \\|  ||   |  \\|  | \\___ \\ ");
	printf("|   Y  \\   ___/ |  |__|  |__\n");
	printf("|__|_|  /|__||___|  /|__|/____ / |___|  / \\___/  |____/|____/\n");
	printf("\033[0m");
	printf("                                by serferna and lortega-  ^_^ \n");
}

void	ft_free(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
		free(lst[i++]);
	free(lst);
}

void	ft_error(char *text)
{
	perror(text);
	exit(127);
}

void	ft_pipe(int fd[2], char *text)
{
	if (pipe(fd) == -1)
		ft_error(text);
}

void	ft_status(int status)
{
	int	signal;

	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGPIPE)
			g_exit_status = 127;
		else
			g_exit_status = signal + 128;
	}
}
