
#include "../../include/minishell.h"

void	change_fd(int fdp[2], int fd[2])
{
	dup2(fdp[READ_END], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fdp[READ_END]);
	close(fd[0]);
	close(fd[1]);
}

void	middle_child(int fdp[2], int fd[2], t_token *list_aux, t_shell *shell)
{
	pid_t		pid;
	t_env_token	*aux;
	char		**l_arraid;

	l_arraid = ft_split(list_aux->content, ' ');
//	printf("hijo second l_arraid --> %s\n", l_arraid[0]);
	pid = fork();
	if (pid < 0)
		ft_error("fork");
	if (pid == 0)
	{
		change_fd(fdp, fd);
		if (pipex_redirect(shell, list_aux) == 0)
		{
			aux = shell->env;
			if (s_build(shell, l_arraid) == 5)
				exe_all(l_arraid, aux);
			exit(0);
		}
	}
	shell->execute = clean_end_state;
	close(fdp[READ_END]);
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	ft_free(l_arraid);
}
