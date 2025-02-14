/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:08 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 12:05:19 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

static t_parse_state	*init_parse_state(void)
{
	t_parse_state	*state;

	state = (t_parse_state *)malloc(sizeof(t_parse_state));
	if (!state)
		return (NULL);
	state->quote_state = NONE;
	state->i = 0;
	state->buf_index = 0;
	state->len = 0;
	return (state);
}

static t_bool	sub_tokenize(t_parse_state *state, char *line, t_shell *shell)
{
	state->quote_state = get_quote_type(state->quote_state, line[state->i]);
	if (state->quote_state == NONE && is_separator(&line[state->i],
			&state->len))
	{
		if (state->buf_index > 0)
		{
			state->buffer[state->buf_index] = '\0';
			if (!add_token(&(shell->tokens), state->buffer))
				return (FALSE);
			state->buf_index = 0;
		}
		ft_strncpy(state->buffer, &line[state->i], state->len);
		state->buffer[state->len] = '\0';
		if (!add_token(&(shell->tokens), state->buffer))
			return (FALSE);
		state->i += state->len;
	}
	else
		state->buffer[state->buf_index++] = line[state->i++];
	return (TRUE);
}

void	tokenize_process(t_state_machine *machine)
{
	t_shell			*shell;
	t_parse_state	*state;

	shell = (t_shell *)machine->context;
	state = init_parse_state();
	while (shell->input[state->i])
	{
		if (!sub_tokenize(state, shell->input, shell))
			return ;
	}
	if (state->buf_index > 0)
	{
		state->buffer[state->buf_index] = '\0';
		add_token(&(shell->tokens), state->buffer);
	}
	free(state);
	machine->execute = assign_type_state;
}

void	tokenize_line(t_shell *shell)
{
	t_state_machine	*machine;

	machine = create_state_machine();
	machine->context = shell;
	machine->execute = tokenize_process;
	machine->is_done = FALSE;
	while (!machine->is_done)
	{
		machine->execute(machine);
	}
}
