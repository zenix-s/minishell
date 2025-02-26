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

static void	last_child(int fd[2], t_token *list_token, t_shell *shell)
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
		line_arraid = ft_split(list_token->content, ' ');
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		if (s_build(shell, line_arraid) == 5)
			exe_all(line_arraid, aux);
	}
	waitpid(pidf, NULL, 0);
	close(fd[WRITE_END]);
}

static void	ft_middle_c(int fdp[2], int fd[2], char **l_arraid, t_shell *shell)
{
	pid_t		pid;
	t_env_token	*aux;

	pid = fork();
	if (pid < 0)
		ft_error("fork");
	if (pid == 0)
	{
		aux = shell->env;
		dup2(fdp[READ_END], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fdp[READ_END]);
		close(fd[0]);
		close(fd[1]);
		if (s_build(shell, l_arraid) == 5)
			exe_all(l_arraid, aux);
		exit(0);
	}
	close(fdp[READ_END]);
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	ft_free(l_arraid);
}

static void	process(int fdp[2], t_shell *shell, t_token *list_token)
{
	int		fd[2];
	t_token	*list_aux;
	int		aux[2];

	list_aux = list_token;
	if (pipe(fd) == -1)
		ft_error("pipe");
	ft_middle_c(fdp, fd, ft_split(list_aux->content, ' '), shell);
	list_aux = list_aux->next;
	while (list_aux != NULL)
	{
		aux[0] = fd[0];
		aux[1] = fd[1];
		if (list_aux->type == PIPE)
			list_aux = list_aux->next;
		if (list_aux->next == NULL )
			last_child(fd, list_aux, shell);
		else
		{
			if (pipe(fd) == -1)
				ft_error("pipe_more");
			ft_middle_c(aux, fd, ft_split(list_aux->content, ' '), shell);
		}
		list_aux = list_aux->next;
	}
}

void	big_pipex(t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	char	**line_arraid;
	t_token	*l_aux;

	l_aux = shell->tokens->next->next;
	line_arraid = previusline(shell);
	if (pipe(fd) == -1)
		ft_error("pipe:");
	pid = fork();
	f_child(fd, pid, line_arraid, shell);
	ft_free(line_arraid);
	close(fd[WRITE_END]);
	process(fd, shell, l_aux);
	waitpid(pid, NULL, 0);
	close(fd[READ_END]);
}
