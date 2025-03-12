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

t_bool	handle_first_redirect(t_parse_state *state)
{
	char	**aux;

	if (!is_string_redirect(state->split_input[state->i]))
	{
		return (TRUE);
	}
	aux = insert_string_on_array(state->split_input, "", state->i);
	if (aux == NULL)
		return (FALSE);
	free(state->split_input);
	state->split_input = aux;
	state->i++;
	return (TRUE);
}

void	handle_pipe_case(t_parse_state *state)
{
	state->is_first = TRUE;
	state->is_next_redirect = FALSE;
	state->i++;
	state->first = state->i;
}

t_bool	merge_with_first(t_parse_state *state)
{
	char	**aux;

	ft_super_strcat(&(state->split_input[state->first]), " ");
	ft_super_strcat(&(state->split_input[state->first]),
		state->split_input[state->i]);
	free(state->split_input[state->i]);
	aux = delete_string_on_array(state->split_input, state->i);
	if (aux == NULL)
		return (FALSE);
	free(state->split_input);
	state->split_input = aux;
	return (TRUE);
}

t_bool	handle_general_case(t_parse_state *state)
{
	if (state->is_first)
	{
		state->is_first = FALSE;
		return (TRUE);
	}
	if (!merge_with_first(state))
		return (FALSE);
	state->i--;
	return (TRUE);
}

t_bool	handle_redirect_case(t_parse_state *state)
{
	if (state->i > 0 && (is_string_redirect(state->split_input[state->i - 1])
			|| is_string_pipe(state->split_input[state->i - 1])))
		return (TRUE);
	if (!merge_with_first(state))
		return (FALSE);
	state->i--;
	return (TRUE);
}

char	**split_input(char *input)
{
	const char	*split[] = {" ", NULL};
	const char	*s_split[] = {">>", "<<", ">", "<", "|", NULL};

	return (special_split(input, split, s_split));
}

t_bool	pre_process_input(t_parse_state *state)
{
	state->split_input = split_input(state->input);
	while (state->split_input[state->i] != NULL)
	{
		if (state->is_first && !handle_first_redirect(state))
			return (FALSE);
		if (is_string_pipe(state->split_input[state->i]))
		{
			handle_pipe_case(state);
			continue ;
		}
		if (is_string_redirect(state->split_input[state->i]))
			state->is_next_redirect = TRUE;
		else
		{
			if (state->is_next_redirect)
			{
				if (!handle_redirect_case(state))
					return (FALSE);
			}
			else if (!handle_general_case(state))
				return (FALSE);
		}
		state->i++;
	}
	return (TRUE);
}

void	tokenize_state(t_shell *shell)
{
	t_parse_state	*state;
	int64_t			i;

	state = factory_parse_state(shell->input);
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
