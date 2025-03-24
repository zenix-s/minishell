/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:27:34 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:27:44 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_cmd(char **l_arraid, t_env_token *list_env)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		return ;
	}
	if (pid == 0)
		exe_all(l_arraid, list_env);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_exit_status = WTERMSIG(status) + 128;
}
