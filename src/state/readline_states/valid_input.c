/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/02/11 23:43:21 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_bool	is_valid_input(t_shell *shell)
{
	if (ft_strlen(shell->input) == 0)
		return (FALSE);
	if (ft_strlen(shell->input) > MAX_INPUT_LENGTH)
	{
		printf("minishell: line exceeds the maximum length\n");
		shell->execute = clean_end_state;
		return (FALSE);
	}
	return (TRUE);
}
