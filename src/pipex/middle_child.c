
#include "../../include/minishell.h"

void	change_fd(int use_fd[2])
{
	dup2(use_fd[READ_END], STDIN_FILENO);
	dup2(use_fd[3], STDOUT_FILENO);
	close(use_fd[READ_END]);
	close(use_fd[2]);
	close(use_fd[3]);
}
void	middle_child(int use_fd[4], t_token *list_aux, t_shell *shell, pid_t child_pids)
{
	t_env_token	*aux;
	char		**l_arraid;

	aux = shell->env;
	l_arraid = ft_split(list_aux->content, ' ');
	child_pids = fork();
	if (child_pids < 0)
		ft_error("fork");
	if (child_pids == 0)
	{
		if (prepare (shell, list_aux) == -1)
			ft_error("dont prepare");
		if (pipex_redirect(shell, list_aux) == 0)
		{
			if (newcmp(l_arraid[0], "ls") != 0)
				change_fd(use_fd);
			if (list_aux->type == BUILT_IN || list_aux->type == EXE)
			{
				if (s_build(shell, l_arraid) == 5)
					exe_all(l_arraid, aux);
				exit(0);
			}
		}
		exit(0);
	}
	shell->execute = clean_end_state;
	close(use_fd[READ_END]);
	close(use_fd[3]);
	ft_free(l_arraid);
}
