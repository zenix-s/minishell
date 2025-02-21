/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:26:30 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:26:32 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstdelone(t_token *lst, void (*del)(void*))
{
	printf("dentro de la funcion del0");
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	printf("dentro de la funcion del1");
	free(lst);
	lst = NULL;
}
