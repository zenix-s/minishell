/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:12:33 by serferna          #+#    #+#             */
/*   Updated: 2025/02/27 21:14:23 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_heredoc_files(t_shell *shell)
{
	int64_t	i;

	if (shell->heredoc_files != NULL)
	{
		i = 0;
		while (shell->heredoc_files[i] != NULL)
		{
			unlink(shell->heredoc_files[i]);
			free(shell->heredoc_files[i]);
			i++;
		}
		free(shell->heredoc_files);
		shell->heredoc_files = NULL;
	}
}

/**
 * @param shell point to struct shell
 * last ite, free the memory to tokens and input
 */
void	clean_end_state(t_shell *shell)
{
	if (shell->input != NULL)
	{
		free(shell->input);
		shell->input = NULL;
	}
	clean_heredoc_files(shell);
	if (shell->read != NULL)
		free(shell->read);
	free_tokens(shell->tokens);
	shell->tokens = NULL;
	shell->input = NULL;
	shell->read = NULL;
	shell->write = NULL;
	shell->is_done = TRUE;
}
