
#include "../../include/minishell.h"

// void	new_waitpid(pid_t pid)
// {

// }

// int	cont_pids(t_shell *shell)
// {
// 	int			result;
// 	t_token		*aux_token;

// 	aux_token = shell->tokens;
// 	result = 0;
// 	while (aux_token)
// 	{
// 		if (aux_token->type == PIPE)
// 			result++;
// 		aux_token = aux_token->next;
// 	}
// 	return (result);
// }



//()///

// static void	process(int fdp[2], t_shell *shell, t_token *list_token, int size)
// {
// 	int		fd[2];
// 	t_token	*list_aux;
// 	int		aux[2];

// 	if (pipe(fd) == -1)
// 		ft_error("pipe");
// 	middle_child(fdp, fd, list_token, shell);
// 	list_aux = list_token;
// 	while (size >= 0)
// 	{
// 		list_aux = next_pipex(list_aux);
// 		aux[0] = fd[0];
// 		aux[1] = fd[1];
// 		if (size == 1)
// 			last_child(fd, shell, list_aux);
// 		else if (size > 1)
// 		{
// 			if (pipe(fd) == -1)
// 				ft_error("pipe_more");
// 			middle_child(aux, fd, list_aux, shell);
// 		}
// 		size--;
// 	}
// }

// void	big_pipex(t_shell *shell)
// {
// 	int		fd[2];
// 	pid_t	pid;
// //	pid_t	*pids;
// 	char	**line_arraid;
// 	t_token	*l_aux;

// //	(pid_t*) malloc(num_procesos * sizeof(pid_t));
// 	l_aux = shell->tokens;
// 	line_arraid = ft_split(shell->tokens->content, ' ');
// 	if (!line_arraid || !line_arraid[0])
// 		ft_error("No command found");
// 	if (pipe(fd) == -1)
// 		ft_error("pipe:");
// 	pid = fork();
// 	f_child(fd, pid, line_arraid, shell);
// 	ft_free(line_arraid);
// 	close(fd[WRITE_END]);
// 	l_aux = next_pipex(l_aux);
// 	process(fd, shell, l_aux, contpipex(l_aux));
// 	waitpid(pid, NULL, 0);
// 	close(fd[READ_END]);
// }
