/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/02/11 23:43:21 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parser.h"

static void	skip_spaces(const char *content, int *i)
{
	while (is_space(content[*i]) && content[*i] != '\0')
		(*i)++;
}

static void	trim_node(t_token *token)
{
	int	quote_state;
	int	i;
	int	j;

	i = 0;
	j = 0;
	quote_state = NONE;
	skip_spaces(token->content, &i);
	while (token->content[i] != '\0')
	{
		quote_state = get_quote_type(quote_state, token->content[i]);
		if (quote_state == NONE && is_space(token->content[i]))
		{
			if (j > 0 && token->content[j - 1] != ' ')
				token->content[j++] = ' ';
			skip_spaces(token->content, &i);
		}
		else
			token->content[j++] = token->content[i++];
	}
	while (j > 0 && is_space(token->content[j - 1]))
		j--;
	token->content[j] = '\0';
}

void	trim_nodes_state(t_shell *shell)
{
	t_token	*current;

	current = shell->tokens;
	while (current)
	{
		trim_node(current);
		current = current->next;
	}
	shell->execute = check_redirect_error_state;
}
