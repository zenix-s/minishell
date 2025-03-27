/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:48:59 by lortega-          #+#    #+#             */
/*   Updated: 2025/03/23 15:49:04 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	change_fd(int use_fd[4])
{
	dup2(use_fd[READ_END], STDIN_FILENO);
	dup2(use_fd[3], STDOUT_FILENO);
	close(use_fd[READ_END]);
	close(use_fd[2]);
	close(use_fd[3]);
}

static void	chill(int use_fd[4], t_shell *shell, t_token *t_aux, char **arraid)
{
	t_env_token	*aux;

	aux = shell->env;
	if (prepare (shell, t_aux) == -1)
		ft_error("dont prepare");
	change_fd(use_fd);
	if (pipex_redirect(shell, t_aux) == 0)
	{
		if (t_aux->type == BUILT_IN || t_aux->type == EXE)
		{
			if (s_build(shell, arraid) == 5)
				exe_all(arraid, aux);
			exit(0);
		}
	}
}

void	m_child(int use_fd[4], t_token *t_aux, t_shell *shell, pid_t child_pids)
{
	char		**l_arraid;

	shell->n_pipex++;
	l_arraid = ft_split(t_aux->content, ' ');
	child_pids = fork();
	if (child_pids < 0)
		ft_error("fork");
	if (child_pids == 0)
	{
		chill(use_fd, shell, t_aux, l_arraid);
		exit(0);
	}
	shell->execute = clean_end_state;
	close(use_fd[READ_END]);
	close(use_fd[3]);
	ft_free(l_arraid);
}
