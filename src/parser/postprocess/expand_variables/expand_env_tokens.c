/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/02/11 23:43:28 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parse.h"

static t_bool	is_valid_init_char(char c)
{
	return (ft_isalpha(c) || c == '_');
}

static t_bool	process_variable_expansion(t_expand_env_state *st,
		t_token *token, t_env_token *env)
{
	st->start++;
	if (!is_valid_init_char(token->content[st->start]))
	{
		st->new_content[st->i++] = '$';
		return (TRUE);
	}
	st->var_name = get_var_name(token->content, &st->start);
	if (!st->var_name)
		return (FALSE);
	st->value = get_env_value(env, st->var_name);
	free(st->var_name);
	st->i = expand_variale(st->new_content, st->i, st->value);
	return (TRUE);
}

static t_bool	expand_env_token(t_token *token, t_env_token *env)
{
	t_expand_env_state	st;

	st.start = 0;
	st.len = 0;
	st.i = 0;
	st.quote = NONE;
	while (token->content[st.start] != '\0')
	{
		st.quote = get_quote_type(st.quote, token->content[st.start]);
		if (token->content[st.start] == '$' && st.quote != SINGLE)
		{
			if (!process_variable_expansion(&st, token, env))
				return (FALSE);
			continue ;
		}
		st.new_content[st.i++] = token->content[st.start++];
	}
	st.new_content[st.i] = '\0';
	free(token->content);
	token->content = ft_strdup(st.new_content);
	if (!token->content)
		return (FALSE);
	return (TRUE);
}

void	expand_env_tokens(t_state_machine *machine)
{
	t_shell		*shell;
	t_token		*current;
	t_env_token	*env;

	shell = (t_shell *)machine->context;
	current = shell->tokens;
	env = shell->env;
	while (current)
	{
		if (!expand_env_token(current, env))
			return ;
		current = current->next;
	}
	machine->execute = trim_nodes;
}
