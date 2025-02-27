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
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->env)
		free_env_tokens(shell->env);
	if (shell->input)
		free(shell->input);
	if (shell->error_message)
		free(shell->error_message);
	free(shell);
}
