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

#include "../../include/minishell.h"
#include <stdio.h>

// zenix-dev ~/Escritorio/test
// × ls >
// bash: error sintáctico cerca del elemento inesperado `newline'

// zenix-dev ~/Escritorio/test
// × ls >>
// bash: error sintáctico cerca del elemento inesperado `newline'

// zenix-dev ~/Escritorio/test
// × ls <<
// bash: error sintáctico cerca del elemento inesperado `newline'
void	check_redirect_newline_error_state(t_shell *shell)
{
	int			i;
	t_token		*current;
	const char	*redirects[] = {">>", ">", "<<", "<", NULL};

	current = shell->tokens;
	while (current)
	{
		if (current->type == REDIRECT)
		{
			i = 0;
			while (redirects[i])
			{
				if (!ft_strcmp(current->content, redirects[i]))
				{
					if (!current->next)
					{
						shell->error_message = ERR_UNEXPECTED_TOKEN_NEWLINE;
						shell->exit_of_failure = FALSE;
						shell->execute = fail_state;
						return ;
					}
				}
				i++;
			}
		}
		current = current->next;
	}
	shell->execute = segurity_state; // TODO: Definir siguiente estado
}
