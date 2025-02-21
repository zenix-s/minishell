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

#include "../../../include/minishell.h"

char	*echo_parser(char *line)
{
	char	*new_line;
	t_quote	in_quotes;
	size_t	i;
	size_t	j;

	in_quotes = 0;
	i = 0;
	j = 0;
	new_line = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		in_quotes = get_quote_type(in_quotes, line[i]);
		if (line[i] == ' ' && in_quotes == NONE && i > 0 && line[i - 1] != ' ')
			new_line[j++] = ' ';
		else
			new_line[j++] = line[i];
	}
	new_line[j] = '\0';
	return (new_line);
}
