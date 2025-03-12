/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_process_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:15 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"

static t_bool	handle_first_redirect(t_parse_state *state)
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

static void	handle_pipe_case(t_parse_state *state)
{
	state->is_first = TRUE;
	state->is_next_redirect = FALSE;
	state->i++;
	state->first = state->i;
}

static t_bool	handle_general_case(t_parse_state *state)
{
	char	**aux;

	if (state->is_first)
	{
		state->is_first = FALSE;
		return (TRUE);
	}
	ft_super_strcat(&(state->split_input[state->first]), " ");
	ft_super_strcat(&(state->split_input[state->first]),
		state->split_input[state->i]);
	free(state->split_input[state->i]);
	aux = delete_string_on_array(state->split_input, state->i);
	if (aux == NULL)
		return (FALSE);
	free(state->split_input);
	state->split_input = aux;
	state->i--;
	return (TRUE);
}

static t_bool	handle_redirect_case(t_parse_state *state)
{
	char	**aux;

	if (state->i > 0 && (is_string_redirect(state->split_input[state->i - 1])
			|| is_string_pipe(state->split_input[state->i - 1])))
		return (TRUE);
	ft_super_strcat(&(state->split_input[state->first]), " ");
	ft_super_strcat(&(state->split_input[state->first]),
		state->split_input[state->i]);
	free(state->split_input[state->i]);
	aux = delete_string_on_array(state->split_input, state->i);
	if (aux == NULL)
		return (FALSE);
	free(state->split_input);
	state->split_input = aux;
	state->i--;
	return (TRUE);
}

t_bool	pre_process_input(t_parse_state *state)
{
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
