/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirect_newline_error_state.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:18:50 by serferna          #+#    #+#             */
/*   Updated: 2025/03/04 17:18:51 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	check_redirect_newline_error_state(t_shell *shell, t_token *current)
{
	if (!current->next)
	{
		shell->error_message = ERR_UNEXPECTED_TOKEN_NEWLINE;
		shell->exit_of_failure = FALSE;
		shell->execute = fail_state;
		return ;
	}
	if (is_special_token(current->next->content))
	{
		shell->error_message = ERR_UNEXPECTED_TOKEN;
		shell->unexpected_token = current->next->content;
		shell->exit_of_failure = FALSE;
		shell->execute = fail_state;
		return ;
	}
}

static void	check_pipe_error_state(t_shell *shell, t_token *current)
{
	if (current->prev == NULL || current->next == NULL)
	{
		shell->error_message = ERR_UNEXPECTED_TOKEN;
		shell->unexpected_token = current->content;
		shell->exit_of_failure = FALSE;
		shell->execute = fail_state;
	}
	else if (is_special_token(current->prev->content)
		|| is_string_pipe(current->next->content))
	{
		shell->error_message = ERR_UNEXPECTED_TOKEN;
		shell->unexpected_token = current->content;
		shell->exit_of_failure = FALSE;
		shell->execute = fail_state;
	}
}

void	check_redirect_error_state(t_shell *shell)
{
	t_token	*current;

	current = shell->tokens;
	while (current)
	{
		if (is_string_redirect(current->content))
		{
			check_redirect_newline_error_state(shell, current);
			if (shell->execute == fail_state)
				return ;
		}
		if (is_string_pipe(current->content))
		{
			check_pipe_error_state(shell, current);
			if (shell->execute == fail_state)
				return ;
		}
		current = current->next;
	}
	shell->execute = parser_end_state;
}
