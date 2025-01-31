/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:08 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 12:05:19 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*tokenize_line(char *line)
{
	t_token	*tokens;
	size_t	i;
	char	buffer[1024];
	int		buf_index;
	int		in_quotes;
	int		consecutive_space;
	size_t	len;

	tokens = NULL;
	i = 0;
	buf_index = 0;
	in_quotes = 0;
	consecutive_space = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			in_quotes = !in_quotes;
			buffer[buf_index++] = line[i++];
		}
		else if (!in_quotes && is_separator(&line[i], &len))
		{
			if (buf_index > 0)
			{
				buffer[buf_index] = '\0';
				add_token(&tokens, buffer);
				buf_index = 0;
			}
			ft_strncpy(buffer, &line[(i)], len);
			buffer[len] = '\0';
			add_token(&tokens, buffer);
			i += len;
		}
		else
		{
			if ((line[(i)] == ' ' || line[(i)] == '\t') && !in_quotes)
			{
				if (consecutive_space == 0)
				{
					buffer[(buf_index)++] = ' ';
					consecutive_space = 1;
				}
				(i)++;
				continue ;
			}
			consecutive_space = 0;
			buffer[(buf_index)++] = line[(i)++];
		}
	}
	if (buf_index > 0)
	{
		buffer[buf_index] = '\0';
		add_token(&tokens, buffer);
	}
	return (tokens);
}
