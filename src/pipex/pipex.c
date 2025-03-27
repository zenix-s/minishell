/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:50:14 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/23 13:50:22 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**postline(t_shell *shell)
{
	t_token	*aux;
	t_token	*prev;
	char	**result;

	shell->n_pipex ++;
	aux = shell->tokens;
	while (aux)
	{
		if (newcmp(aux->content, "|") == 0)
		{
			if (aux->next != NULL)
			{
				prev = aux->next;
				result = (ft_split(prev->content, ' '));
				return (result);
			}
		}
		aux = aux->next;
	}
	return (NULL);
}

static t_token	*real_search(t_shell *shell)
{
	t_token	*result;

	result = shell->tokens;
	while (result)
	{
		if (result->type == PIPE)
		{
			if (!result->next)
				return (NULL);
			result = result->next;
			return (result);
		}
		result = result->next;
	}
	return (NULL);
}

void	s_child(int *fd, int pid2, char **l_arraid, t_shell *shell)
{
	t_env_token	*aux;
	t_token		*aux_token;

	aux_token = real_search(shell);
	aux = shell->env;
	if (pid2 < 0)
		return ;
	if (pid2 == 0)
	{
		if (prepare(shell, aux_token) == -1)
			return ;
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		if (pipex_redirect(shell, aux_token) == 0)
		{
			if (aux_token->type == BUILT_IN || aux_token->type == EXE)
			{
				if (s_build(shell, l_arraid) == 5)
					exe_all(l_arraid, aux);
			}
		}
		close(fd[READ_END]);
		exit(0);
	}
	shell->execute = clean_end_state;
}

void	f_child(int *fd, int pid1, char **l_arraid, t_shell *shell)
{
	t_env_token	*aux;
	t_token		*aux_token;

	aux_token = shell->tokens;
	aux = shell->env;
	if (pid1 < 0)
		ft_error("fork:");
	if (pid1 == 0)
	{
		if (prepare(shell, aux_token) == -1)
			exit(1);
		close(fd[READ_END]);
		dup2(fd[WRITE_END], STDOUT_FILENO);
		if (pipex_redirect(shell, aux_token) == 0)
		{
			if (aux_token->type == BUILT_IN || aux_token->type == EXE)
			{
				if (s_build(shell, l_arraid) == 5)
					exe_all(l_arraid, aux);
			}
		}
		close(fd[WRITE_END]);
		exit(0);
	}
	shell->execute = clean_end_state;
}

void	pipex(t_shell *shell)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**line_arraid;
	int		status;

	status = 0;
	line_arraid = ft_split(shell->tokens->content, ' ');
	if (!line_arraid || !line_arraid[0])
		ft_error("No command found");
	if (pipe(fd) == -1)
		ft_error("pipex");
	pid1 = fork();
	f_child(fd, pid1, line_arraid, shell);
	ft_free(line_arraid);
	line_arraid = postline(shell);
	pid2 = fork();
	s_child(fd, pid2, line_arraid, shell);
	ft_free(line_arraid);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	ft_status(status);
}
