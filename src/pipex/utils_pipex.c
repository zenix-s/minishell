/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 13:54:34 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/23 13:54:39 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//quiza aqui podria estar la busqueda de la redireccion


// el nombre esta al reves!
//devuelve el char **
/*
es posible que esta funcion muera ---
*/
char	**previusline(t_shell *shell)
{
	t_token	*aux;
	t_token	*prev;
	char	**result;

	aux = shell->tokens;
	prev = aux;
	while (aux)
	{
		if (ft_strcmp(aux->content, "|") == 0)
		{
			result = (ft_split(prev->content, ' '));
			return (result);
		}
		prev = aux;
		aux = aux->next;
	}
	return (NULL);
}

char	**postline(t_shell *shell)
{
	t_token	*aux;
	t_token	*prev;
	char	**result;

	aux = shell->tokens;
	while (aux)
	{
		if (ft_strcmp(aux->content, "|") == 0)
		{
			prev = aux->next;
			result = (ft_split(prev->content, ' '));
			return (result);
		}
		aux = aux->next;
	}
	return (NULL);
}
