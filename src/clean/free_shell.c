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
	if (shell->tokens != NULL)
		free_tokens(shell->tokens);
	if (shell->env != NULL)
		free_env_tokens(shell->env);
	if (shell->input != NULL)
	{
		free(shell->input);
		shell->input = NULL;
	}
	free(shell);
}
