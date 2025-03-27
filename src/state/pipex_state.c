/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:18:16 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/25 22:18:22 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	select_pipex(t_shell *shell, int mode)
{
	shell->n_pipex = 0;
	if (mode == 1)
		pipex(shell);
	if (mode != 1)
		big_pipex(shell);
	shell->execute = clean_end_state;
}

void	pipex_state(t_shell *shell)
{
	int		mode;
	t_token	*env_aux;

	env_aux = shell->tokens;
	mode = 0;
	if (env_aux && env_aux->next)
	{
		while (env_aux)
		{
			if (env_aux->type == PIPE)
				mode++;
			env_aux = env_aux->next;
		}
		if (mode != 0)
			select_pipex(shell, mode);
	}
	if (mode == 0)
		shell->execute = redirect_state;
}
