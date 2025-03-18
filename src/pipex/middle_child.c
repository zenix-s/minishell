
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

	aux = shell->env;
	l_arraid = ft_split(list_aux->content, ' ');
	pid = fork();
	if (pid < 0)
		ft_error("fork");
	if (pid == 0)
	{
		if (prepare (shell, list_aux) == -1)
			ft_error("dont prepare");
		if (pipex_redirect(shell, list_aux) == 0)
		{
			if (list_aux->type == BUILT_IN || list_aux->type == EXE)
			{
				change_fd(fdp, fd);
				if (s_build(shell, l_arraid) == 5)
					exe_all(l_arraid, aux);
				exit(0);
			}
		}
	}
	shell->execute = clean_end_state;
	close(fdp[READ_END]);
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	ft_free(l_arraid);
}
