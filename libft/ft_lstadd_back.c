/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lortega- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:26:30 by lortega-          #+#    #+#             */
/*   Updated: 2025/02/08 19:26:32 by lortega-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstadd_back(t_token **lst, t_token *new_token)
{
	t_token	*temp;

	if (!new_token)
		return ;
	temp = ft_lstlast(*lst);
	if (temp)
		temp->next = new_token;
	else
		*lst = new_token;
}
