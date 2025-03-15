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

static void	last_child(int fd[2], t_shell *shell, t_token *list_aux)
{
	pid_t		pidf;
	t_env_token	*aux;
	char		**line_arraid;

	pidf = fork();
	aux = shell->env;
	if (pidf < 0)
		ft_error("fork");
	if (pidf == 0)
	{
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		if (prepare (shell, list_aux) == -1)
			ft_error("dont prepare");
		if (pipex_redirect(shell, list_aux) == 0)
		{
			if (list_aux->type == BUILT_IN || list_aux->type == EXE)
			{
				line_arraid = ft_split(list_aux->content, ' ');
				if (s_build(shell, line_arraid) == 5)
					exe_all(line_arraid, aux);
				ft_free(line_arraid);
			}
		}
	}
	shell->execute = clean_end_state;
	waitpid(pidf, NULL, 0);
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

static void	process(int fdp[2], t_shell *shell, t_token *list_token, int size)
{
	int		fd[2];
	t_token	*list_aux;
	int		aux[2];

	if (pipe(fd) == -1)
		ft_error("pipe");
	middle_child(fdp, fd, list_token, shell);
	list_aux = list_token;
	while (size >= 0)
	{
		list_aux = next_pipex(list_aux);
		aux[0] = fd[0];
		aux[1] = fd[1];
		if (size == 1)
			last_child(fd, shell, list_aux);
		else if (size > 1)
		{
			if (pipe(fd) == -1)
				ft_error("pipe_more");
			middle_child(aux, fd, list_aux, shell);
		}
		size--;
	}
}

void	big_pipex(t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	char	**line_arraid;
	t_token	*l_aux;

	l_aux = shell->tokens;
	line_arraid = ft_split(shell->tokens->content, ' ');
	if (!line_arraid || !line_arraid[0])
		ft_error("No command found");
	if (pipe(fd) == -1)
		ft_error("pipe:");
	pid = fork();
	f_child(fd, pid, line_arraid, shell);
	ft_free(line_arraid);
	close(fd[WRITE_END]);
	l_aux = next_pipex(l_aux);
	process(fd, shell, l_aux, contpipex(l_aux));
	waitpid(pid, NULL, 0);
	close(fd[READ_END]);
}
