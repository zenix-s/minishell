
#include "../../include/minishell.h"

t_bool	count_tokens_not_none_quotes(t_bool *in_token, uint64_t *count,
		uint64_t *i, t_quote quote_state)
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

void	count_tokens_regular_split_found(t_bool *in_token, uint64_t *i,
		const uint64_t split_len)
{
	if (*in_token)
	{
		*in_token = FALSE;
	}
	(*i) += split_len;
}

void	count_tokens_regular_split_not_found(t_bool *in_token, uint64_t *count,
		uint64_t *i)
{
	if (!*in_token)
	{
		*in_token = TRUE;
		(*count)++;
	}
	(*i)++;
}

int	count_tokens(char *input, const char **split, const char **s_split)
{
	uint64_t	count;
	uint64_t	i;
	int		quote_state;
	t_bool		in_token;
	uint64_t	split_len;

	count = 0;
	i = 0;
	quote_state = NONE;
	in_token = FALSE;
	while (input[i])
	{
		quote_state = get_quote_type(quote_state, input[i]);
		if (count_tokens_not_none_quotes(&in_token, &count, &i, quote_state))
			continue ;
		split_len = is_string_in_array(input + i, s_split);
		if (count_tokens_special_split(&in_token, &count, &i, split_len))
			continue ;
		split_len = is_string_in_array(input + i, split);
		if (split_len > 0)
			count_tokens_regular_split_found(&in_token, &i, split_len);
		else
			count_tokens_regular_split_not_found(&in_token, &count, &i);
	}
	return (count);
}

// Allocate memory for result array
char	**allocate_result_array(uint64_t token_count)
{
	char	**result;

	result = (char **)malloc((token_count + 1) * sizeof(char *));
	return (result);
}

typedef struct s_splitter
{
	char		**result;
	uint64_t	result_idx;
	int64_t		start;
	t_quote		q_state;

	int64_t		i;
}				t_splitter;

void	add_splitter_token(t_splitter *splitter, char *input, int64_t start,
		int64_t len)
{
	splitter->result[splitter->result_idx] = (char *)malloc((len + 1)
			* sizeof(char));
	ft_strncpy(splitter->result[splitter->result_idx], input + start, len);
	splitter->result[splitter->result_idx][len] = '\0';
	splitter->result_idx++;
}

void	process_special_splitter(t_splitter *splitter, char *input, int64_t i,
		uint64_t split_len)
{
	if (splitter->start != -1)
	{
		add_splitter_token(splitter, input, splitter->start, i
			- splitter->start);
		splitter->start = -1;
	}
	add_splitter_token(splitter, input, i, split_len);
}

void	process_regular_splitter(t_splitter *splitter, char *input, int64_t i)
{
	if (splitter->start != -1)
	{
		add_splitter_token(splitter, input, splitter->start, i
			- splitter->start);
		splitter->start = -1;
	}
}

void	parse_splitter_tokens(char *input, const char **split,
		const char **s_split, t_splitter *aux)
{
	uint64_t	split_len;
	t_quote		n_q_state;

	aux->i = 0;
	while (input[aux->i])
	{
		n_q_state = get_quote_type(aux->q_state, input[aux->i]);
		if (aux->q_state == NONE && n_q_state != NONE && aux->start == -1)
			aux->start = aux->i;
		if (aux->q_state != NONE)
		{
			if (aux->start == -1)
				aux->start = aux->i;
			aux->i++;
			aux->q_state = n_q_state;
			continue ;
		}
		split_len = is_string_in_array(input + aux->i, s_split);
		if (split_len > 0)
		{
			process_special_splitter(aux, input, aux->i, split_len);
			aux->i += split_len;
			continue ;
		}
		split_len = is_string_in_array(input + aux->i, split);
		if (split_len > 0)
		{
			process_regular_splitter(aux, input, aux->i);
			aux->i += split_len;
		}
		else
		{
			if (aux->start == -1)
				aux->start = aux->i;
			aux->i++;
		}
		aux->q_state = n_q_state;
	}
	if (aux->start != -1)
		add_splitter_token(aux, input, aux->start, aux->i - aux->start);
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
	aux->result = allocate_result_array(token_count);
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
