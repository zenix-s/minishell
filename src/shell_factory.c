/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_factory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:35:36 by serferna          #+#    #+#             */
/*   Updated: 2025/02/25 22:35:43 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_shell	*shell_factory(char **env)
{
	t_shell	*shell;

	shell = (t_shell *)ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->is_done = FALSE;
	shell->execute = NULL;
	shell->tokens = NULL;
	shell->input = NULL;
	shell->error_message = NULL;
	shell->exit_of_failure = FALSE;
	shell->read = NULL;
	shell->write = NULL;
	shell->pending_inputs = NULL;
	shell->is_here_doc = FALSE;
	shell->n_pipex = 0;
	shell->heredoc_files = NULL;
	if (!create_list_env(env, &(shell->env)))
		return (0);
	return (shell);
}
