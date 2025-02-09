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
			st.start++;
			if (!ft_isalpha(token->content[st.start])
				&& token->content[st.start] != '_')
			{
				st.new_content[st.i++] = '$';
				continue ;
			}
			while (ft_isalnum(token->content[st.start + st.len])
				|| token->content[st.start + st.len] == '_')
				st.len++;
			st.var_name = ft_strndup(&token->content[st.start], st.len);
			if (!st.var_name)
				return (FALSE);
			st.value = get_env_value(env, st.var_name);
			free(st.var_name);
			if (st.value)
				while (*st.value)
					st.new_content[st.i++] = *st.value++;
			st.start += st.len;
			st.len = 0;
		}
		else
			st.new_content[st.i++] = token->content[st.start++];
	}
	st.new_content[st.i] = '\0';
	free(token->content);
	token->content = ft_strdup(st.new_content);
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
