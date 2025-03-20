/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:00:30 by serferna          #+#    #+#             */
/*   Updated: 2025/02/27 21:00:30 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_state(int mod)
{
	if (mod == -1)
		perror("Error opening file");
}

void	fail_state(t_shell *shell)
{
	if (shell->error_message != NULL)
	{
		if (newcmp(shell->error_message, ERR_UNEXPECTED_TOKEN) == 0)
			printf("syntax error near unexpected token `%s'\n",
				shell->unexpected_token);
		else
			printf("minishell: %s\n", shell->error_message);
	}
	if (shell->exit_of_failure)
	{
		free_shell(shell);
		exit(EXIT_FAILURE);
	}
	shell->execute = clean_end_state;
}
