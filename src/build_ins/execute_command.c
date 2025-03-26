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
#include <sys/types.h>
#include <dirent.h>


static int is_directory(const char *path) {
    DIR *dir = opendir(path); // Intentamos abrir el path como un directorio
    if (dir) {
        closedir(dir); // Si la apertura fue exitosa, cerramos el directorio
        return 1; // Es un directorio
    } else {
        return 0; // No es un directorio o hubo un error
    }
}

void	execute_cmd(char **l_arraid, t_env_token *list_env)
{
	pid_t	pid;
	int		status;

	status = 0;
	set_sigaction_for_child();
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		return ;
	}
	if (pid == 0)
	{
		if (is_directory(l_arraid[0]) == 1)
		{
			printf("minishell: %s: Is a directory\n", l_arraid[0]);
			exit(126);
		}
		exe_all(l_arraid, list_env);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_exit_status = WTERMSIG(status) + 128;
}
