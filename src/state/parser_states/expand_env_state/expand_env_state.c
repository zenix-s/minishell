/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_state.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:20:15 by serferna          #+#    #+#             */
/*   Updated: 2025/02/25 19:38:11 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"
#include "../../../../include/parser.h"

static t_bool	process_value_for_export(t_expand_env_state *st, t_token *token)
{
	char	*new_value;
	char	tmp;

	tmp = token->content[st->start - ft_strlen(st->var_name) - 2];
	if (st->start > 0 && tmp != '=')
	{
		st->idiot = TRUE;
		return (TRUE);
	}
	new_value = (char *)malloc(sizeof(char) * (ft_strlen(st->value) + 3));
	if (!new_value)
		return (FALSE);
	new_value[0] = '"';
	ft_strcpy(new_value + 1, st->value);
	new_value[ft_strlen(st->value) + 1] = '"';
	new_value[ft_strlen(st->value) + 2] = '\0';
	free(st->value);
	st->value = new_value;
	return (TRUE);
}

static char	*get_env_final_value(const t_env_token *env, t_expand_env_state *st,
		t_token *token)
{
	if (newcmp(st->var_name, "?") == 0)
		return (ft_itoa(g_exit_status));
	if (st->var_name[0] == '\"' || st->var_name[0] == '\'')
		return (ft_strdup(st->var_name));
	st->value = ft_strdup(get_env_value(env, st->var_name));
	if (token->type == BUILT_IN && token->built_in == EXPORT && st->value
		&& !st->idiot && !process_value_for_export(st, token))
		return (NULL);
	else if (st->quote == NONE && st->value && st->value[0] != '\0'
		&& !add_quotes(st->value, &st->value))
		return (NULL);
	return (st->value);
}

static t_bool	process_variable_expansion(t_expand_env_state *st,
		t_token *token, const t_env_token *env)
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
	st->value = get_env_final_value(env, st, token);
	free(st->var_name);
	st->i = expand_variale(st->new_content, st->i, st->value);
	free(st->value);
	return (TRUE);
}

static t_bool	expand_env_token(t_token *token, t_env_token *env)
{
	t_expand_env_state	st;

	st.start = 0;
	st.len = 0;
	st.i = 0;
	st.quote = NONE;
	st.idiot = FALSE;
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

void	expand_env_state(t_shell *shell)
{
	t_token		*current;
	t_env_token	*env;

	current = shell->tokens;
	env = shell->env;
	while (current)
	{
		if (!expand_env_token(current, env))
			return ;
		current = current->next;
	}
	shell->execute = trim_nodes_state;
}
