/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:15 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/minishell.h"

static t_bool	is_valid_quoting(uint64_t *i, char *line, t_quote in_quotes)
{
	if ((line[*i] == '\"' || line[*i] == '\'') && in_quotes == NONE)
	{
		(*i)++;
		return (TRUE);
	}
	return (FALSE);
}

char	*echo_parser(char *line)
{
	char		*new_line;
	int		in_quotes;
	uint64_t	i;
	uint64_t	j;

	in_quotes = NONE;
	i = 0;
	j = 0;
	new_line = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (is_valid_quoting(&i, line, in_quotes))
			continue ;
		in_quotes = get_quote_type(in_quotes, line[i]);
		if (line[i] == ' ' && in_quotes == NONE && i > 0 && line[i - 1] != ' ')
			new_line[j++] = ' ';
		else
			new_line[j++] = line[i];
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}
