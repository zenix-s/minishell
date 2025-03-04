/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:22:37 by serferna          #+#    #+#             */
/*   Updated: 2025/02/27 21:24:30 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param shell Puntero a la estructura shell
 * Ultimo estado de la iteracion, libera la memoria de los tokens y el input
 * para permitir la salida del programa.
 */
void exit_state(t_shell *shell)
{
  	free_shell(shell);
	exit(EXIT_SUCCESS);
}