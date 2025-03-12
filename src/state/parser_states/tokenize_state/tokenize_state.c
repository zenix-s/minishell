/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:15 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

static t_parse_state	*factory_parse_state(char *input)
{
	t_parse_state	*state;

	state = (t_parse_state *)malloc(sizeof(t_parse_state));
	if (!state)
		return (NULL);
	state->i = 0;
	state->first = 0;
	state->is_first = TRUE;
	state->is_next_redirect = FALSE;
	state->input = input;
	state->split_input = NULL;
	return (state);
}

char	**split_input(char *input)
{
	const char	*split[] = {" ", NULL};
	const char	*s_split[] = {">>", "<<", ">", "<", "|", NULL};

	return (special_split(input, split, s_split));
}

void	tokenize_state(t_shell *shell)
{
	t_parse_state	*state;
	int64_t			i;

	state = factory_parse_state(shell->input);
	state->split_input = split_input(state->input);
	if (!pre_process_input(state))
	{
		free(state);
		shell->execute = clean_end_state;
		return ;
	}
	i = 0;
	while (state->split_input[i] != NULL)
	{
		if (!string_is_null_or_whitespace(state->split_input[i]))
			add_token(&(shell->tokens), state->split_input[i]);
		free(state->split_input[i]);
		i++;
	}
	free(state->split_input);
	free(state);
	shell->execute = assign_type_state;
}
