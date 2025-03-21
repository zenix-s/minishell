/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:49:45 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/23 13:49:51 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*next_pipex(t_token *list_token)
{
	t_token	*l_aux;

	l_aux = list_token;
	while (l_aux && l_aux->type != PIPE)
		l_aux = l_aux->next;
	if (l_aux && l_aux->next)
		l_aux = l_aux->next;
	return (l_aux);
}

static void	last_child(int fd[2], t_shell *shell, t_token *list_aux, pid_t child_pids)
{
	t_env_token	*aux;
	char		**line_arraid;

	child_pids = fork();
	if (child_pids < 0)
		ft_error("fork");
	aux = shell->env;
	if (child_pids == 0)
	{
		line_arraid = ft_split(list_aux->content, ' ');
//		printf ("%s\n", line_arraid[0]);
		if (newcmp(line_arraid[0], "ls") != 0)
			dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		if (prepare (shell, list_aux) == -1)
			ft_error("dont prepare");
		if (pipex_redirect(shell, list_aux) == 0)
		{
			if (list_aux->type == BUILT_IN || list_aux->type == EXE)
			{
				if (s_build(shell, line_arraid) == 5)
					exe_all(line_arraid, aux);
				ft_free(line_arraid);
			}
		}
		exit (0);
	}
	shell->execute = clean_end_state;
	close(fd[WRITE_END]);
}

static int	contpipex(t_token *list_aux)
{
	int		size;
	t_token	*list_cont;

	size = 0;
	list_cont = list_aux;
	while (list_cont)
	{
		if (list_cont->type == PIPE)
			size++;
		list_cont = list_cont->next;
	}
	return (size);
}

static void	process(int fdp[2], t_shell *shell, int size, pid_t *child_pids)
{
	int		fd[2];
	t_token	*token_aux;
	int		aux[2];
	int		i;
	int		use_fd[4];


	i = 2;
	token_aux = next_pipex(shell->tokens);
	if (pipe(fd) == -1)
		ft_error("pipe");
	use_fd[0] = fdp[0];
	use_fd[1] = fdp[1];
	use_fd[2] = fd[0];
	use_fd[3] = fd[1];
	middle_child(use_fd, token_aux, shell, child_pids[1]);
	size --;
	while (size > 0)
	{
		token_aux = next_pipex(token_aux);
		aux[0] = fd[0];
		aux[1] = fd[1];
		if (size == 1)
			last_child(fd, shell, token_aux, child_pids[i]);
		else
		{
			if (pipe(fd) == -1)
				ft_error("pipe_more");
			use_fd[0] = aux[0];
			use_fd[1] = aux[1];
			use_fd[2] = fd[0];
			use_fd[3] = fd[1];
			middle_child(use_fd, token_aux, shell, child_pids[i]);
		}
		size--;
		i++;
	}
	close(fd[READ_END]);
}

void	big_pipex(t_shell *shell)
{
	int		fd[2];
	char	**line_arraid;
	t_token	*token_aux;
	pid_t	*child_pids;
	int		size;
	int		status;

	line_arraid = ft_split(shell->tokens->content, ' ');
	if (!line_arraid || !line_arraid[0])
		ft_error("No command found");
	if (pipe(fd) == -1)
		ft_error("pipe:");
	token_aux = shell->tokens;
	size = contpipex(token_aux);
	child_pids = ft_calloc(size + 1, sizeof(pid_t));
	child_pids[0] = fork();
	f_child(fd, child_pids[0], line_arraid, shell);
	ft_free(line_arraid);
	close(fd[WRITE_END]);
	process(fd, shell, size, child_pids);
	close(fd[READ_END]);
	size = 0;	
	while (size < contpipex(token_aux) + 1)
	{
		waitpid(child_pids[size], &status, 0);
		size++;
	}
	free(child_pids);
	close(fd[READ_END]);
}
