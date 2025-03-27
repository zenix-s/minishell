/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:39:05 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/25 15:39:09 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	stnd_in(t_token *env_aux, t_shell *aux, int mode)
{
	char	**cmd;
	int		file;
	char	*name;
	int		stdin_copy;

	file = -1;
	cmd = ft_split(env_aux->content, ' ');
	name = env_aux->next->next->content;
	if (mode == 4)
		file = open(name, O_RDONLY);
	if (mode == 1)
		file = open("file.txt", O_RDONLY);
	stdin_copy = dup(STDIN_FILENO);
	if (file == -1)
		return (-1);
	if (dup2(file, STDIN_FILENO) == -1)
		ft_error("Error redirecting stdout");
	if (s_build(aux, cmd) == 5)
		execute_cmd(cmd, aux->env);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
	close(file);
	ft_free(cmd);
	return (0);
}

int	new_stnd_in(t_shell *shell)
{
	char	**cmd;
	int		file;
	char	*name;
	int		stdin_copy;

	file = -1;
	cmd = ft_split(shell->tokens->content, ' ');
	name = shell->read;
	file = open(name, O_RDONLY);
	stdin_copy = dup(STDIN_FILENO);
	if (file == -1)
		return (-1);
	if (dup2(file, STDIN_FILENO) == -1)
		ft_error("Error redirecting stdout");
	if (s_build(shell, cmd) == 5)
		execute_cmd(cmd, shell->env);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
	close(file);
	ft_free(cmd);
	return (0);
}
