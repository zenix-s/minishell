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
 * @param shell point to struct shell
 * last ite, free the memory to tokens and input
 */

void	exit_state(t_shell *shell)
{
	int	exit_status;

	exit_status = shell->exit_status;
	free_shell(shell);
	exit(exit_status);
}
