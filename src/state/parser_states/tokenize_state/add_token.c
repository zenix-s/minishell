/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:00 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:42 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

t_bool	add_token(t_token **head, char *content)
{
	t_token	*new_token;
	t_token	*temp;

	new_token = create_token(content);
	if (!new_token)
		return (FALSE);
	if (!*head)
	{
		*head = new_token;
		return (TRUE);
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
	new_token->prev = temp;
	return (TRUE);
}
