/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:08 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 12:05:19 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"


void	tokenize_line(t_shell *shell)
{
	t_state_machine	*machine;

	machine = create_state_machine();
	machine->context = shell;
	machine->execute = tokenize_state;
	machine->is_done = FALSE;
	while (!machine->is_done)
	{
		machine->execute(machine);
	}
}
