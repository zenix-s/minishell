/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:15 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parse.h"

static t_bool	trim_node(t_token *token)
{
	t_quote	quote_state;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote_state = NONE;
	while (is_parse_space(token->content[i]) && token->content[i] != '\0')
		i++;
	while (token->content[i] != '\0')
	{
		quote_state = get_quote_type(quote_state, token->content[i]);
		if (quote_state == NONE && is_parse_space(token->content[i]))
		{
			if (j > 0 && token->content[j - 1] != ' ')
				token->content[j++] = ' ';
			while (is_parse_space(token->content[i]))
				i++;
		}
		else
			token->content[j++] = token->content[i++];
	}
	while (j > 0 && is_parse_space(token->content[j - 1]))
		j--;
	token->content[j] = '\0';
	return (TRUE);
}

t_bool	trim_nodes(t_shell *shell)
{
	t_token	*current;

	current = shell->tokens;
	while (current)
	{
		if (!trim_node(current))
			return (FALSE);
		current = current->next;
	}
	return (TRUE);
}
