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
#include "../../../../include/parse.h"

char	*get_first_word(const char *content)
{
	uint64_t	start;
	uint64_t	end;
	t_quote		quote;

	start = 0;
	start = 0;
	end = 0;
	quote = NONE;
	while (content[start] && is_parse_space(content[start]))
		start++;
	quote = get_quote_type(NONE, content[start]);
	if (content[start] == '\'' || content[start] == '"')
		start++;
	end = start;
	while (content[end] && (quote != NONE || !is_parse_space(content[end])))
	{
		quote = get_quote_type(quote, content[end]);
		if (quote == NONE && is_parse_space(content[end]))
			break ;
		end++;
	}
	if (quote == NONE && (content[end - 1] == '\'' || content[end - 1] == '"'))
		end--;
	return (strndup(content + start, end - start));
}

int	is_in_array(const char *str, const char *array[])
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (strcmp(str, array[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	assign_token_type(t_state_machine *machine)
{
	t_shell		*shell;
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit", NULL};
	const char	*separators[] = {"<<", ">>", "<", ">", NULL};
	t_token		*token;
	char		*first_word;

	shell = (t_shell *)machine->context;
	token = shell->tokens;
	while (token)
	{
		first_word = get_first_word(token->content);
		if (first_word && is_in_array(first_word, builtins))
			token->type = BUILT_IN;
		else if (is_in_array(token->content, separators))
			token->type = REDIRECT;
		else if (strcmp(token->content, "|") == 0)
			token->type = PIPE;
		else
			token->type = EXE;
		free(first_word);
		token = token->next;
	}
	machine->execute = expand_env_tokens;
}
