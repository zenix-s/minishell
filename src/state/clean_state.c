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
#include <stdlib.h>
#include <string.h>

/**
 * @param shell Puntero a la estructura shell
 * Ultimo estado de la iteracion, libera la memoria de los tokens y el input
 * para permitir la siguiente iteracion.
 */
void	clean_end_state(t_shell *shell)
{
	if (shell->input != NULL)
	{
		free(shell->input);
		shell->input = NULL;
	}
	free_tokens(shell->tokens);
	shell->tokens = NULL;
	shell->input = NULL;
	shell->read = NULL;
	shell->write = NULL;
	// ft_free(shell->here);
	shell->is_done = TRUE;
}
