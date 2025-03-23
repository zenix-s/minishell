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

#include "../../include/minishell.h"
#include "../../include/parser.h"

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

void	readline_state(t_shell *shell)
{
	shell->input = readline("minishell: ");
	if (!shell->input)
	{
		free_shell(shell);
		exit(EXIT_SUCCESS);
	}
	while (has_unclosed_quotes(shell->input))
	{
		if (!manage_unclosed_quotes(&shell->input))
			break ;
	}
	add_history(shell->input);
	shell->execute = tokenize_state;
}
