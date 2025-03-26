/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:55:35 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/23 13:55:38 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_shell(t_shell *shell)
{
	int64_t	i;

	if (shell->tokens != NULL)
		free_tokens(shell->tokens);
	if (shell->env != NULL)
		free_env_tokens(shell->env);
	if (shell->input != NULL)
	{
		free(shell->input);
		shell->input = NULL;
	}
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
	if (shell->pending_inputs != NULL)
		ft_free(shell->pending_inputs);
	if (shell->read != NULL)
		free(shell->read);
	free(shell);
}
