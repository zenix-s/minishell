/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quote_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:15 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_quote_type(t_quote quote_state, char chr)
{
	if (chr == '"' && quote_state != SINGLE)
	{
		if (quote_state == DOUBLE)
			quote_state = NONE;
		else
			quote_state = DOUBLE;
	}
	else if (chr == '\'' && quote_state != DOUBLE)
	{
		if (quote_state == SINGLE)
			quote_state = NONE;
		else
			quote_state = SINGLE;
	}
	return (quote_state);
}
