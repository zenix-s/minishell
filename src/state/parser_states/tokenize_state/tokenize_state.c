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

static t_parse_state	*init_parse_state(void)
{
	t_parse_state	*state;

	state = (t_parse_state *)malloc(sizeof(t_parse_state));
	if (!state)
		return (NULL);
	state->i = 0;
	state->first = 0;
	state->is_first = TRUE;
	state->is_next_redirect = FALSE;
	return (state);
}

char	**handle_first_redirect(char **result, int64_t *i)
{
	char	**aux;

	if (is_string_in_array(result[*i], g_split_redirect))
	{
		aux = insert_string_on_array(result, "", *i);
		if (aux == NULL)
			return (NULL);
		free(result);
		result = aux;
		(*i)++;
	}
	return (result);
}

void	handle_pipe_case(t_parse_state *state)
{
	state->is_first = TRUE;
	state->is_next_redirect = FALSE;
	state->i++;
	state->first = state->i;
}

char	**merge_with_first(char **result, t_parse_state *state)
{
	char	**aux;

	ft_super_strcat(&(result[state->first]), " ");
	ft_super_strcat(&(result[state->first]), result[state->i]);
	free(result[state->i]);
	aux = delete_string_on_array(result, state->i);
	if (aux == NULL)
		return (NULL);
	free(result);
	return (aux);
}

char	**handle_general_case(char **result, t_parse_state *state)
{
	if (state->is_first)
	{
		state->is_first = FALSE;
		// state->i++;
		return (result);
	}
	result = merge_with_first(result, state);
	if (!result)
		return (NULL);
	--state->i;
	return (result);
}

char	**handle_redirect_case(char **result, t_parse_state *state)
{
	if (is_string_in_array(result[state->i - 1], g_split_redirect)
		&& state->i > 0)
		return (result);
	result = merge_with_first(result, state);
	if (!result)
		return (NULL);
	--state->i;
	return (result);
}

char	**pre_process_input(char *input, t_parse_state *state)
{
	char	**result;

	result = split_input(input, g_split_space, g_split_redirect_pipe);
	while (result[state->i] != NULL)
	{
		if (state->is_first)
		{
			result = handle_first_redirect(result, &state->i);
			if (!result)
				return (NULL);
		}
		if (is_string_in_array(result[state->i], g_split_pipe))
		{
			handle_pipe_case(state);
			continue ;
		}
		if (is_string_in_array(result[state->i], g_split_redirect))
			state->is_next_redirect = TRUE;
		else if (state->is_next_redirect)
			result = handle_redirect_case(result, state);
		else
			result = handle_general_case(result, state);
		state->i++;
	}
	return (result);
}

void	tokenize_state(t_shell *shell)
{
	t_parse_state	*state;
	char			**res;
	int64_t			i;

	state = init_parse_state();
	res = pre_process_input(shell->input, state);
	i = 0;
	while (res[i] != NULL)
	{
		add_token(&(shell->tokens), res[i]);
		free(res[i]);
		i++;
	}
	free(res);
	free(state);
	shell->execute = assign_type_state;
}
