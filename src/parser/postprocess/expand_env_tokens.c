/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:15 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parse.h"

static t_bool	expand_env_token(t_token *token, t_env_token *env)
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
