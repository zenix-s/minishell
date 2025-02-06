
#include "../include/minishell.h"

void	s_child(int *fd, int pid2, char **l_arraid, t_token *l_env)
{
	int	fd_dest;

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
		select_build(l_arraid, l_env, 2);
		ft_error("exe");
	}
}

void	f_child(int *fd, int pid1, char **l_arraid, t_token *l_env)
{
	int		texto;

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
		select_build(l_arraid, l_env, 1);
		ft_error("exe");
	}
}

/**
 @ fd[2] ->contiene dos enteros ( READ_END and WRITE_END)
 @ pidx  ->almacena identificadores de proceso PID
argv
 para llamar a la funcion se puede usar pipex(line_arraid, obtain_env(l_aux))
*/
void	pipex(char **line_arraid, t_token *l_env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		ft_error("pipex");
	pid1 = fork();
	f_child(fd, pid1, line_arraid, l_env);
	pid2 = fork();
	s_child(fd, pid2, line_arraid, l_env);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
