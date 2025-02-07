
#include "../../include/minishell.h"

void	execute_command(char **line_arraid, t_token *list_env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		return ;
	}
	if (pid == 0)
		exe_all(line_arraid, list_env);
	else
		waitpid(pid, NULL, 0);
}
