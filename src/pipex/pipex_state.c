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


//hay que seguir por le big pipex! 
void	select_pipex(t_shell *shell, int mode)
{
	t_token		*aux;
	char		**cmd;
	t_env_token	*moreaux;

	cmd = NULL;
	aux = shell->tokens;
	while (aux)
	{
		if (aux->type == REDIRECT)
			cmd = postline(shell);
		aux = aux->next;
	}
	if (mode == 1)
	{
		if (cmd != NULL)
		{
			moreaux = shell->env;
			if (s_build(shell, cmd) == 5)
				exe_all(cmd, moreaux);
		}
		else
			pipex(shell);
	}
	if (mode != 1)
		big_pipex(shell);
}

void	pipex_state(t_shell *shell)
{
	int		mode;
	t_token	*env_aux;

	env_aux = shell->tokens;
	mode = 0;
	if (env_aux->next)
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
	if (mode != 0)
		shell->is_done = TRUE;
	else
		shell->execute = select_all;
}
