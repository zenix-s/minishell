
#include "../include/minishell.h"

void	s_child(int *fd, int pid2, char **l_arraid, t_shell **shell)
{
	int	fd_dest;
	t_shell	*aux;

	aux = *shell;
	if (pid2 < 0)
		return ;
	if (pid2 == 0)
	{
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		fd_dest = open("file.txt", O_CREAT | O_WRONLY |O_APPEND, 0644);
		dup2(fd_dest, STDOUT_FILENO);
		close(fd_dest);
		select_build(&aux, l_arraid);
		ft_error("exe");
	}
}


void	f_child(int *fd, int pid1, char **l_arraid, t_shell **shell)
{
	int		texto;
	t_shell	*aux;

	aux = *shell;
	if (pid1 < 0)
		ft_error("fork:");
	if (pid1 == 0)
	{
		close(fd[READ_END]);
		texto = open("file.txt", O_CREAT | O_WRONLY |O_APPEND, 0644);
		dup2(texto, STDIN_FILENO);
		close(texto);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		select_build(&aux, l_arraid);
		ft_error("exe");
	}
}

static char	**preline(t_shell **shell)
{
	t_token	*aux;
	t_token	*prev;
	char	**result;

	aux = (*shell)->tokens;
	prev = aux;
	while (aux)
	{
		if (ft_strcmp(aux->content, "|") == 0)
		{
			result = (ft_split(prev->content, ' '));
			return (result);
		}
		prev = aux;
		aux = aux->next;
	}
	return (NULL);
}

static char	**postline(t_shell **shell)
{
	t_token	*aux;
	t_token	*prev;
	char	**result;

	aux = (*shell)->tokens;
	while (aux)
	{
		if (ft_strcmp(aux->content, "|") == 0)
		{
			prev = aux->next;
			result = (ft_split(prev->content, ' '));
			return (result);
		}
		aux = aux->next;
	}
	return (NULL);
}

/*
 @ fd[2] ->contiene dos enteros ( READ_END and WRITE_END)
 @ pidx  ->almacena identificadores de proceso PID
*/
void	pipex(t_shell **shell)
{
	int			fd[2];
	pid_t		pid1;
	pid_t		pid2;
	char		**line_arraid;

	line_arraid = preline(shell);
	if (pipe(fd) == -1)
		ft_error("pipex");
	pid1 = fork();
	f_child(fd, pid1, line_arraid, shell);
	ft_free(line_arraid);
	pid2 = fork();
	line_arraid = postline(shell);
	s_child(fd, pid2, line_arraid, shell);
	ft_free(line_arraid);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

