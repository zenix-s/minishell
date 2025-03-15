/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:15:34 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/24 15:15:38 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	stnd_out(t_token *env_aux, t_shell *aux, int mode)
{
	char	**cmd;
	int		file;
	char	*name;
	int		stdout_copy;

	cmd = ft_split(env_aux->content, ' ');
	name = env_aux->next->next->content;
	if (mode == 2)
		file = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (mode == 3)
		file = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	stdout_copy = dup(STDOUT_FILENO);
	if (file == -1)
		ft_error("Error opening file");
	if (dup2(file, STDOUT_FILENO) == -1)
		ft_error("Error redirecting stdout");
	if (s_build(aux, cmd) == 5)
		execute_cmd(cmd, aux->env);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
	close(file);
	ft_free(cmd);
}
