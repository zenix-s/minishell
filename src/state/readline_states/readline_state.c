/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/02/11 23:43:21 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../../../include/parser.h"

int	has_unclosed_quotes(const char *line)
{
	size_t	i;
	int		quote_state;

	i = 0;
	quote_state = NONE;
	while (line[i])
	{
		quote_state = get_quote_type(quote_state, line[i]);
		i++;
	}
	return (quote_state != NONE);
}

int	manage_unclosed_quotes(char **line)
{
	char	*new_line;
	char	*temp;

	new_line = readline("- ");
	if (!new_line)
		return (0);
	temp = *line;
	*line = malloc(ft_strlen(*line) + ft_strlen(new_line) + 2);
	if (!*line)
	{
		free(temp);
		free(new_line);
		exit(EXIT_FAILURE);
	}
	ft_strcpy(*line, temp);
	ft_strcat(*line, "\n");
	ft_strcat(*line, new_line);
	free(temp);
	free(new_line);
	return (1);
}

t_bool	handle_pending_input(t_shell *shell)
{
	char	**temp;

	if (shell->pending_inputs != NULL
		&& get_array_string_size(shell->pending_inputs) > 0)
	{
		shell->input = ft_strdup(shell->pending_inputs[0]);
		temp = delete_string_on_array(shell->pending_inputs, 0);
		if (temp == NULL)
		{
			shell->error_message = ERR_MALLOC;
			shell->execute = fail_state;
			return (TRUE);
		}
		free(shell->pending_inputs[0]);
		free(shell->pending_inputs);
		shell->pending_inputs = temp;
		shell->execute = tokenize_state;
		return (TRUE);
	}
	if (shell->pending_inputs != NULL)
	{
		ft_free(shell->pending_inputs);
		shell->pending_inputs = NULL;
	}
	return (FALSE);
}

t_bool	handle_input(t_shell *shell)
{
	char		**tokens;
	char		**temp;
	const char	*split[] = {"\n", NULL};

	tokens = special_split(shell->input, split, NULL);
	if (tokens == NULL)
	{
		shell->execute = clean_end_state;
		return (TRUE);
	}
	free(shell->input);
	shell->input = ft_strdup(tokens[0]);
	temp = delete_string_on_array(tokens, 0);
	if (temp == NULL)
	{
		shell->error_message = ERR_MALLOC;
		shell->execute = fail_state;
		return (TRUE);
	}
	free(tokens[0]);
	free(tokens);
	shell->pending_inputs = temp;
	add_history(shell->input);
	return (FALSE);
}

void	readline_state(t_shell *shell)
{
	init_sigaction();
	if (handle_pending_input(shell))
		return ;
	shell->input = readline("minishell: ");
	if (!shell->input)
	{
		printf("exit\n");
		free_shell(shell);
		exit(EXIT_SUCCESS);
	}
	if (!is_valid_input(shell))
		return ;
	while (has_unclosed_quotes(shell->input))
	{
		if (!manage_unclosed_quotes(&shell->input))
			break ;
	}
	if (string_is_null_or_whitespace(shell->input))
	{
		shell->execute = clean_end_state;
		return ;
	}
	if (handle_input(shell))
		return ;
	shell->execute = tokenize_state;
}
