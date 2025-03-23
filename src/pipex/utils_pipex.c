/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:36:06 by lortega-          #+#    #+#             */
/*   Updated: 2025/03/23 16:36:09 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*next_pipex(t_token *list_token)
{
	t_token	*l_aux;

	l_aux = list_token;
	while (l_aux && l_aux->type != PIPE)
		l_aux = l_aux->next;
	if (l_aux && l_aux->next)
		l_aux = l_aux->next;
	return (l_aux);
}

int	contpipex(t_token *list_aux)
{
	int		size;
	t_token	*list_cont;

	size = 0;
	list_cont = list_aux;
	while (list_cont)
	{
		if (list_cont->type == PIPE)
			size++;
		list_cont = list_cont->next;
	}
	return (size);
}

t_token	*prepare_next_time(t_token *token_aux, int aux[2], int fd[2])
{
	token_aux = next_pipex(token_aux);
	aux[0] = fd[0];
	aux[1] = fd[1];
	return (token_aux);
}
