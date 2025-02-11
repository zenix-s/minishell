/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:08 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 12:05:19 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	env_list_add_back(t_env_token **head, t_env_token *new_env)
{
	t_env_token	*temp;

	if (!*head)
	{
		*head = new_env;
		return (TRUE);
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_env;
	return (TRUE);
}
