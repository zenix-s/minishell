/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:00 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:42 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bool	count_tokens_in_quotes(t_bool *in_token, uint64_t *count, uint64_t *i,
		t_quote quote_state)
{
	if (quote_state == NONE)
		return (FALSE);
	if (!*in_token)
	{
		*in_token = TRUE;
		(*count)++;
	}
	(*i)++;
	return (TRUE);
}

t_bool	count_tokens_special_split(t_bool *in_token, uint64_t *count,
		uint64_t *i, uint64_t s_split_len)
{
	if (s_split_len == 0)
		return (FALSE);
	if (*in_token)
	{
		*in_token = FALSE;
	}
	(*count)++;
	(*i) += s_split_len;
	return (TRUE);
}

void	count_tokens_regular_split(t_bool *in_token, uint64_t *count,
		uint64_t *i, uint64_t split_len)
{
	if (*in_token)
		*in_token = FALSE;
	else
	{
		*in_token = TRUE;
		(*count)++;
	}
	if (split_len > 0)
		(*i) += split_len;
	else
		(*i)++;
}

int	count_tokens(char *input, const char **split, const char **s_split)
{
	uint64_t	count;
	uint64_t	i;
	int			quote_state;
	t_bool		in_token;
	uint64_t	split_len;

	count = 0;
	i = 0;
	quote_state = NONE;
	in_token = FALSE;
	while (input[i])
	{
		quote_state = get_quote_type(quote_state, input[i]);
		if (count_tokens_in_quotes(&in_token, &count, &i, quote_state))
			continue ;
		split_len = is_string_in_array(input + i, s_split);
		if (count_tokens_special_split(&in_token, &count, &i, split_len))
			continue ;
		split_len = is_string_in_array(input + i, split);
		count_tokens_regular_split(&in_token, &count, &i, split_len);
	}
	return (count);
}
