
#include "../../include/minishell.h"

void	change_fd(int use_fd[2])
{
	dup2(use_fd[READ_END], STDIN_FILENO);
	dup2(use_fd[3], STDOUT_FILENO);
	close(use_fd[READ_END]);
	close(use_fd[2]);
	close(use_fd[3]);
}
//int fdp[2], int fd[2]
pid_t	middle_child(int use_fd[4], t_token *list_aux, t_shell *shell)
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
				change_fd(use_fd);
				if (s_build(shell, l_arraid) == 5)
					exe_all(l_arraid, aux);
				exit(0);
			}
			else
				exit (0);
		}
		exit(0);
	}
	shell->execute = clean_end_state;
	close(use_fd[READ_END]);
	close(use_fd[3]);
	ft_free(l_arraid);
	return (pid);
}
