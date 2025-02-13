
#include "../include/minishell.h"

//TODO 
//cuando entras en algo que no existe da leak

static void	ft_last_children(int fd[2], t_token **list_token, t_shell **shell)
{
	pid_t	pidf;
	t_shell	*aux;
	char	**line_arraid;

	aux = *shell;
	pidf = fork();
	if (pidf < 0)
		ft_error("fork");
	if (pidf == 0)
	{
		line_arraid = ft_split((*list_token)->content, ' ');
		dup2(fd[READ_END], STDIN_FILENO);
		select_build(&aux, line_arraid);
		close(fd[READ_END]);
		close(STDOUT_FILENO);
		exit(0);
	}
	else
		waitpid(pidf, NULL, 0);
}


static void	ft_middle_c(int fdp[2], int fd[2], char **l_arraid, t_shell **shell)
{
	pid_t	pid;
	t_shell	*aux;

	aux = *shell;
	pid = fork();
	if (pid < 0)
		ft_error("fork");
	if (pid == 0)
	{
		close(fd[READ_END]);
		dup2(fdp[READ_END], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		select_build(&aux, l_arraid);
		exit(0);
	}
	close(fdp[READ_END]);
	close(fd[WRITE_END]);
}

static void	process(int fdp[2], t_shell **shell, t_token **list_token)
{
	int		fd[2];
	int		aux[2];
	int		bool;
	char	**line_arraid;
	t_token	*list_aux;

	list_aux = *list_token;
	bool = 0;
	while (list_aux != NULL)
	{
		if (pipe(fd) == -1)
			ft_error("pipe");
		if (list_aux->type == PIPE)
			list_aux = list_aux->next;
		line_arraid = ft_split(list_aux->content, ' ');
		if (bool != 0)
			ft_middle_c(aux, fd, line_arraid, shell);
		else if (list_aux->next != NULL && bool == 0)
			ft_middle_c(fdp, fd, line_arraid, shell);
		ft_free(line_arraid);
		bool++;
		aux[0] = fd[0];
		aux[1] = fd[1];
		list_aux = list_aux->next;
	}
	ft_last_children(fd, list_token, shell);
}

void	big_pipex(t_shell **shell)
{
	int		fd[2];
	pid_t	pid;
	char	**line_arraid;
	t_token	*l_aux;

	l_aux = (*shell)->tokens->next->next;
	line_arraid = preline(shell);
	if (pipe(fd) == -1)
		ft_error("pipe:");
	pid = fork();
	f_child(fd, pid, line_arraid, shell);
	ft_free(line_arraid);
	close(fd[WRITE_END]);
	process(fd, shell, &l_aux);
	close(fd[READ_END]);
}
