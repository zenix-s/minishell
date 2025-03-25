/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:00 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:42 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	finalize_token(t_splitter *splitter, char *input, int64_t end)
{
	if (splitter->start != -1)
	{
		splitter->result[splitter->result_idx++] = ft_strndup(input
				+ splitter->start, end - splitter->start);
		splitter->start = -1;
	}
}

t_bool	handle_special_split(t_splitter *aux, char *input, const char **s_split)
{
	uint64_t	split_len;

	split_len = is_string_in_array(input + aux->i, s_split);
	if (split_len > 0)
	{
		finalize_token(aux, input, aux->i);
		aux->result[aux->result_idx++] = ft_strndup(input + aux->i, split_len);
		aux->i += split_len;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	handle_normal_split(t_splitter *aux, char *input, const char **split)
{
	uint64_t	split_len;

	split_len = is_string_in_array(input + aux->i, split);
	if (split_len > 0)
	{
		finalize_token(aux, input, aux->i);
		aux->i += split_len;
		return (TRUE);
	}
	return (FALSE);
}

void	parse_splitter_tokens(char *input, const char **split,
		const char **s_split, t_splitter *aux)
{
	t_quote	n_q_state;

	aux->i = 0;
	while (input[aux->i])
	{
		n_q_state = get_quote_type(aux->q_state, input[aux->i]);
		if (aux->q_state == NONE && n_q_state != NONE && aux->start == -1)
			aux->start = aux->i;
		if (aux->q_state != NONE)
		{
			aux->i++;
			aux->q_state = n_q_state;
			continue ;
		}
		if (handle_special_split(aux, input, s_split))
			continue ;
		if (handle_normal_split(aux, input, split))
			continue ;
		if (aux->start == -1)
			aux->start = aux->i;
		aux->i++;
		aux->q_state = n_q_state;
	}
	finalize_token(aux, input, aux->i);
	aux->result[aux->result_idx] = NULL;
}

char	**special_split(char *input, const char **split, const char **s_split)
{
	uint64_t	token_count;
	t_splitter	*aux;
	char		**result;

	if (input == NULL)
		return (NULL);
	token_count = count_tokens(input, split, s_split);
	aux = (t_splitter *)malloc(sizeof(t_splitter));
	if (!aux)
		return (NULL);
	aux->result = malloc((token_count + 1) * sizeof(char *));
	if (aux->result == NULL)
	{
		free(aux);
		return (NULL);
	}
	aux->result_idx = 0;
	aux->q_state = NONE;
	aux->start = -1;
	aux->i = 0;
	parse_splitter_tokens(input, split, s_split, aux);
	result = aux->result;
	free(aux);
	return (result);
}
