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

static void	exe_l_child(t_shell *shell, t_token *list_aux)
{
	t_env_token	*aux;
	char		**line_arraid;

	aux = shell->env;
	line_arraid = ft_split(list_aux->content, ' ');
	if (s_build(shell, line_arraid) == 5)
		exe_all(line_arraid, aux);
	ft_free(line_arraid);
}

static void	las_child(int fd[2], t_shell *shell, t_token *list_aux, pid_t child)
{
	shell->n_pipex++;
	child = fork();
	if (child < 0)
		ft_error("fork");
	if (child == 0)
	{
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
		close(fd[WRITE_END]);
		if (prepare (shell, list_aux) == -1)
			ft_error("dont prepare");
		if (pipex_redirect(shell, list_aux) == 0)
		{
			if (list_aux->type == BUILT_IN || list_aux->type == EXE)
				exe_l_child(shell, list_aux);
		}
		exit (0);
	}
	shell->execute = clean_end_state;
	close(fd[WRITE_END]);
}

static void	change_use_fd(int use_fd[4], int fdp[2], int fd[2])
{
	use_fd[0] = fdp[0];
	use_fd[1] = fdp[1];
	use_fd[2] = fd[0];
	use_fd[3] = fd[1];
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
	ft_pipe(fd, "first pipe the middle");
	change_use_fd(use_fd, fdp, fd);
	m_child(use_fd, token_aux, shell, child_pids[1]);
	while (size > 0)
	{
		token_aux = prepare_next_time(token_aux, aux, fd);
		if (size == 1)
			las_child(fd, shell, token_aux, child_pids[i++]);
		else
		{
			ft_pipe(fd, "pipe the middle");
			change_use_fd(use_fd, aux, fd);
			m_child(use_fd, token_aux, shell, child_pids[i++]);
		}
		size--;
	}
	close(fd[READ_END]);
}

void	big_pipex(t_shell *shell)
{
	int		fd[2];
	char	**line_arraid;
	t_token	*token_aux;
	pid_t	*child_pids;

	line_arraid = ft_split(shell->tokens->content, ' ');
	if (!line_arraid || !line_arraid[0])
		ft_error("No command found");
	if (pipe(fd) == -1)
		ft_error("pipe:");
	token_aux = shell->tokens;
	child_pids = ft_calloc(contpipex(token_aux) + 1, sizeof(pid_t));
	child_pids[0] = fork();
	f_child(fd, child_pids[0], line_arraid, shell);
	ft_free(line_arraid);
	close(fd[WRITE_END]);
	process(fd, shell, contpipex(token_aux) - 1, child_pids);
	close(fd[READ_END]);
	ft_waitpid(token_aux, child_pids);
	free(child_pids);
}
