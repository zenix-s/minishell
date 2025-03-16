/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_separator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:06 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:06 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_separator(const char *line, size_t *sep_len)
{
	const char	*separators[] = {"<<", ">>", "<", ">", "|", NULL};
	size_t		len;
	int			i;

	i = 0;
	while (separators[i])
	{
		len = ft_strlen(separators[i]);
		if (ft_strncmp(line, separators[i], len) == 0)
		{
			*sep_len = len;
			return (1);
		}
		i++;
	}
	return (0);
}

uint64_t	is_special_token(const char *str)
{
	const char	*search[] = {"<<", ">>", "<", ">", "|", NULL};

	return (is_string_in_array(str, search));
}

uint64_t	is_string_redirect(const char *str)
{
	const char	*search[] = {">>", "<<", ">", "<", NULL};

	return (is_string_in_array(str, search));
}

uint64_t	is_string_pipe(const char *str)
{
	const char	*search[] = {"|", NULL};

	return (is_string_in_array(str, search));
}
