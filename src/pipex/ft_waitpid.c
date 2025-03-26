/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_waitpid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:21:14 by lortega-          #+#    #+#             */
/*   Updated: 2025/03/23 16:21:16 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_waitpid(t_token	*token_aux, pid_t *child_pids)
{
	int		status;
	int		size;
	int		cont;

	status = 0;
	size = contpipex(token_aux) + 1;
	cont = 0;
	while (cont < size)
	{
		waitpid(child_pids[cont], &status, 0);
		if (cont == size - 1)
			ft_status(status);
		cont++;
	}
}
