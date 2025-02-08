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
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>

// This function is used to trim the leading and trailing spaces from nodes
// -- echo   "hello   world"  hello -- Should be converted to --echo "hello   world" hello--
// since i dont want to realloc the memory just move the content to the start of the node and turn the rest of the node to NULL

t_bool	is_parse_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

t_bool	trim_node(t_token *token)
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

char	*expand_env_var(const char *line, uint64_t *i, const t_env_token *env)
{
	uint64_t	len;
	char		*var_name;
	char		*value;
	uint64_t	start;

	start = *i + 1;
	len = 0;
	if (!ft_isalpha(line[start]) && line[start] != '_')
		return (NULL);
	while (ft_isalnum(line[start + len]) || line[start + len] == '_')
		len++;
	var_name = ft_strndup(&line[start], len);
	if (!var_name)
		return (NULL);
	value = get_env_value(env, var_name);
	free(var_name);
	*i = start + len;
	return (value);
}

typedef struct s_expand_env_state
{
	uint64_t	len;
	char		*var_name;
	char		*value;
	uint64_t	start;
	char		new_content[1024];
	uint64_t	i;
	t_quote		quote_state;
}				t_expand_env_state;

t_bool	expand_env_token(t_token *token, t_env_token *env)
{
	t_expand_env_state	state;

	state.start = 0;
	state.len = 0;
	state.i = 0;
	state.quote_state = NONE;
	while (token->content[state.start])
	{
		state.quote_state = get_quote_type(state.quote_state,
				token->content[state.start]);
		if (token->content[state.start] == '$' && state.quote_state != SINGLE)
		{
			state.start++;
			if (!ft_isalpha(token->content[state.start])
				&& token->content[state.start] != '_')
			{
				state.new_content[state.i++] = '$';
				continue ;
			}
			while (ft_isalnum(token->content[state.start + state.len])
				|| token->content[state.start + state.len] == '_')
				state.len++;
			state.var_name = ft_strndup(&token->content[state.start],
					state.len);
			if (!state.var_name)
				return (FALSE);
			state.value = get_env_value(env, state.var_name);
			free(state.var_name);
			if (state.value)
				while (*state.value)
					state.new_content[state.i++] = *state.value++;
			state.start += state.len;
			state.len = 0;
		}
		else
			state.new_content[state.i++] = token->content[state.start++];
	}
	state.new_content[state.i] = '\0';
	free(token->content);
	token->content = ft_strdup(state.new_content);
	if (!token->content)
		return (FALSE);
	return (TRUE);
}

t_bool	expand_env_tokens(t_shell *shell)
{
	t_token		*current;
	t_env_token	*env;

	current = shell->tokens;
	env = shell->env;
	while (current)
	{
		if (!expand_env_token(current, env))
			return (FALSE);
		current = current->next;
	}
	return (TRUE);
}

typedef struct s_parse_state
{
	t_quote		quote_state;
	uint64_t	i;
	uint64_t	buf_index;
	char		buffer[1024];
	uint64_t	len;
}				t_parse_state;

t_parse_state	*init_parse_state(void)
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

t_bool	sub_tokenize(t_parse_state *state, char *line, t_shell *shell)
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

t_token	*tokenize_line(char *line, t_shell *shell)
{
	t_parse_state	*state;

	state = init_parse_state();
	while (line[state->i])
	{
		if (!sub_tokenize(state, line, shell))
			return (NULL);
	}
	if (state->buf_index > 0)
	{
		state->buffer[state->buf_index] = '\0';
		add_token(&(shell->tokens), state->buffer);
	}
	expand_env_tokens(shell);
	trim_nodes(shell);
	return (shell->tokens);
}
