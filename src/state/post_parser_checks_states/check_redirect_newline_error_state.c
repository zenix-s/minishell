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

void	check_redirect_newline_error_state(t_shell *shell)
{
	t_token		*current;

	current = shell->tokens;
	while (current)
	{
		if (is_string_redirect(current->content))
		{
			if (!current->next)
			{
				shell->error_message = ERR_UNEXPECTED_TOKEN_NEWLINE;
				shell->exit_of_failure = FALSE;
				shell->execute = fail_state;
				return ;
			}
		}
		current = current->next;
	}
	shell->execute = parser_end_state;
}
