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

static t_token	*last_pipex(t_shell *shell)
{
	t_token	*result;
	t_token	*aux;

	aux = shell->tokens;

	while (aux)
	{
		if (aux->type == PIPE)
		{
			aux = aux->next;
			result = aux;
		}
		aux = aux->next;
	}
	return (result);
}

static void	last_child(int fd[2], t_shell *shell)
{
	pid_t		pidf;
	t_env_token	*aux;
	char		**line_arraid;
	t_token		*t_for_use;

	pidf = fork();
	aux = shell->env;
	if (pidf < 0)
		ft_error("fork");
	if (pidf == 0)
	{
		t_for_use = last_pipex(shell);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		if (pipex_redirect(shell, t_for_use) == 0)
		{
			line_arraid = ft_split(t_for_use->content, ' ');
			if (s_build(shell, line_arraid) == 5)
				exe_all(line_arraid, aux);
			ft_free(line_arraid);
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
static void	process(int fdp[2], t_shell *shell, t_token *list_token)
{
	int		fd[2];
	t_token	*list_aux;
	int		aux[2];
	int		size;

	list_aux = list_token;
	if (pipe(fd) == -1)
		ft_error("pipe");
//	printf("primera --- > ptata\n");
	middle_child(fdp, fd, list_aux, shell);
//	printf("segunda --- > ptata\n");
	list_aux = list_aux->next;
	size = contpipex(list_aux);
	while (list_aux != NULL)
	{
//		printf("ptata\n");
		aux[0] = fd[0];
		aux[1] = fd[1];
		if (list_aux->type == PIPE && size > 1)
		{
			if (pipe(fd) == -1)
				ft_error("pipe_more");
			middle_child(aux, fd, list_aux, shell);
			size--;
		}
		if (list_aux->type == PIPE && size == 1)
			last_child(fd, shell);
		list_aux = list_aux->next;
	}
}

static t_token	*next_pipex(t_shell *shell)
{
	t_token	*l_aux;

	l_aux = shell->tokens;
	while (l_aux && l_aux->type != PIPE)
	{
		l_aux = l_aux->next;
	}
	l_aux = l_aux->next;
	return (l_aux);
}

void	big_pipex(t_shell *shell)
{
	int		fd[2];
	pid_t	pid;
	char	**line_arraid;
	t_token	*l_aux;

	prepare_in_loop(shell);
	l_aux = next_pipex(shell);
	line_arraid = ft_split(shell->tokens->content, ' ');
	if (!line_arraid || !line_arraid[0])
		ft_error("No command found");
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
