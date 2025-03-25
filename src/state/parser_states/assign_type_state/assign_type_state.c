/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nodes_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/02/11 23:43:36 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"
#include "../../../../include/parser.h"

char	*get_first_word(const char *content)
{
	uint64_t	start;
	uint64_t	end;
	int			quote;

	start = 0;
	start = 0;
	while (content[start] && is_space(content[start]))
		start++;
	quote = get_quote_type(NONE, content[start]);
	if (content[start] == '\'' || content[start] == '"')
		start++;
	end = start;
	while (content[end] && (quote != NONE || !is_space(content[end])))
	{
		quote = get_quote_type(quote, content[end]);
		if (quote == NONE && is_space(content[end]))
			break ;
		end++;
	}
	if (quote == NONE && (content[end - 1] == '\'' || content[end - 1] == '"'))
		end--;
	return (strndup(content + start, end - start));
}

t_built_in_type	get_built_in_type(const char *str)
{
	if (newcmp(str, "echo") == 0)
		return (ECHO);
	if (newcmp(str, "cd") == 0)
		return (CD);
	if (newcmp(str, "pwd") == 0)
		return (PWD);
	if (newcmp(str, "export") == 0)
		return (EXPORT);
	if (newcmp(str, "unset") == 0)
		return (UNSET);
	if (newcmp(str, "env") == 0)
		return (ENV);
	if (newcmp(str, "exit") == 0)
		return (EXIT);
	return (-1);
}

static void	set_token_type(t_token *token, t_cmd_type type,
		t_built_in_type built_in)
{
	token->type = type;
	token->built_in = built_in;
}

void	assign_type_state(t_shell *shell)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit", NULL};
	const char	*separators[] = {"<<", ">>", "<", ">", NULL};
	t_token		*token;
	char		*first_word;

	token = shell->tokens;
	while (token)
	{
		first_word = get_first_word(token->content);
		if (first_word && is_string_in_array(first_word, builtins))
			set_token_type(token, BUILT_IN, get_built_in_type(first_word));
		else if (is_string_in_array(token->content, separators))
			set_token_type(token, REDIRECT, UNDEFINED);
		else if (newcmp(token->content, "|") == 0)
			set_token_type(token, PIPE, UNDEFINED);
		else
			set_token_type(token, EXE, UNDEFINED);
		free(first_word);
		token = token->next;
	}
	shell->execute = expand_env_state;
}
