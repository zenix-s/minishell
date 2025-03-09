/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:15 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/parser.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static t_parse_state	*init_parse_state(void)
{
	t_parse_state	*state;

	state = (t_parse_state *)malloc(sizeof(t_parse_state));
	if (!state)
		return (NULL);
	state->quote_state = NONE;
	state->i = 0;
	state->buf_index = 0;
	state->len = 0;
	return (state);
}

static t_bool	sub_tokenize(t_parse_state *state, char *line, t_shell *shell)
{
	state->quote_state = get_quote_type(state->quote_state, line[state->i]);
	if (state->quote_state == NONE && is_separator(&line[state->i],
			&state->len))
	{
		if (state->buf_index > 0)
		{
			state->buffer[state->buf_index] = '\0';
			if (!add_token(&(shell->tokens), state->buffer))
				return (FALSE);
			state->buf_index = 0;
		}
		ft_strncpy(state->buffer, &line[state->i], state->len);
		state->buffer[state->len] = '\0';
		if (!add_token(&(shell->tokens), state->buffer))
			return (FALSE);
		state->i += state->len;
	}
	else
		state->buffer[state->buf_index++] = line[state->i++];
	return (TRUE);
}

char	**insert_string(char *arr[], char *str, int pos)
{
	int64_t	size;
	int64_t	i;
	char	**new_arr;

	size = 0;
	if (arr == NULL || str == NULL || pos < 0)
		return (NULL);
	while (arr[size] != NULL)
		size++;
	if (pos > size)
		return (NULL);
	new_arr = (char **)malloc((size + 2) * sizeof(char *));
	if (new_arr == NULL)
		return (NULL);
	i = -1;
	while (++i < pos)
		new_arr[i] = arr[i];
	new_arr[pos] = ft_strdup(str);
	while (i < size)
	{
		new_arr[i + 1] = arr[i];
		i++;
	}
	new_arr[size + 1] = NULL;
	return (new_arr);
}

void	empty_string(char *str)
{
	int64_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = '\0';
		i++;
	}
}

char	**delete_string(char *arr[], int pos)
{
	int64_t	size;
	int64_t	i;
	char	**new_arr;

	size = 0;
	if (arr == NULL || pos < 0)
		return (NULL);
	while (arr[size] != NULL)
		size++;
	if (pos >= size)
		return (NULL);
	new_arr = (char **)malloc(size * sizeof(char *));
	if (new_arr == NULL)
		return (NULL);
	i = -1;
	while (++i < pos)
		new_arr[i] = arr[i];
	--i;
	while (++i < size - 1)
		new_arr[i] = arr[i + 1];
	new_arr[size - 1] = NULL;
	return (new_arr);
}

char    **handle_first_redirect(char **result, int64_t *i)
{
    char    **aux;
    const char    *redirect[] = {">>", "<<", ">", "<", NULL};

    if (is_string_in_array(result[*i], redirect))
    {
        aux = insert_string(result, "", *i);
        if (aux == NULL)
            return (NULL);
        free(result);
        result = aux;
        (*i)++;
    }
    return (result);
}

void    handle_pipe_case(t_bool *is_first, t_bool *is_next_redirect, int64_t *i, int64_t *first)
{
    *is_first = TRUE;
    *is_next_redirect = FALSE;
    (*i)++;
    *first = *i;
}

char    **merge_with_first(char **result, int64_t *i, int64_t first)
{
    char    **aux;

    ft_super_strcat(&result[first], " ");
    ft_super_strcat(&result[first], result[*i]);
    free(result[*i]);
    aux = delete_string(result, *i);
    if (aux == NULL)
        return (NULL);
    free(result);
    return (aux);
}

char    **pre_process_input(char *input)
{
    const char    *split[] = {" ", NULL};
    const char    *s_split[] = {">>", "<<", ">", "<", "|", NULL};
    const char    *redirect[] = {">>", "<<", ">", "<", NULL};
    const char    *pipe[] = {"|", NULL};
    char        **result = split_input(input, split, s_split);
    int64_t        i = 0, first = 0;
    t_bool        is_first = TRUE, is_next_redirect = FALSE;

    while (result[i] != NULL)
    {
        if (is_first)
        {
            result = handle_first_redirect(result, &i);
            if (!result) return (NULL);
            is_first = FALSE;
        }
        if (is_string_in_array(result[i], pipe))
        {
            handle_pipe_case(&is_first, &is_next_redirect, &i, &first);
            continue;
        }
        if (is_string_in_array(result[i], redirect))
            is_next_redirect = TRUE;
        else if (is_next_redirect)
        {
            if (is_string_in_array(result[i - 1], redirect) && i > 0)
            {
                i++;
                continue;
            }
            result = merge_with_first(result, &i, first);
            if (!result) return (NULL);
            --i;
        }
        i++;
    }
    return (result);
}

// char	**pre_process_input(char *input)
// {
// 	const char	*split[] = {" ", NULL};
// 	const char	*s_split[] = {">>", "<<", ">", "<", "|", NULL};
// 	const char	*redirect[] = {">>", "<<", ">", "<", NULL};
// 	const char	*pipe[] = {"|", NULL};
// 	char		**result;
// 	char		**aux;
// 	int64_t		i;
// 	t_bool		is_first;
// 	int64_t		first;
// 	t_bool		is_next_redirect;

// 	result = split_input(input, split, s_split);
// 	i = 0;
// 	first = 0;
// 	is_first = TRUE;
// 	is_next_redirect = FALSE;
// 	while (result[i] != NULL)
// 	{
// 		if (is_first)
// 		{
// 			if (is_string_in_array(result[i], redirect))
// 			{
// 				aux = insert_string(result, "", i);
// 				if (aux == NULL)
// 					return (NULL);
// 				free(result);
// 				result = aux;
// 				i++;
// 			}
// 			is_first = FALSE;
// 		}
// 		if (is_string_in_array(result[i], pipe))
// 		{
// 			is_first = TRUE;
// 			is_next_redirect = FALSE;
// 			i++;
// 			first = i;
// 			continue ;
// 		}
// 		if (is_string_in_array(result[i], redirect))
// 			is_next_redirect = TRUE;
// 		else if (is_next_redirect)
// 		{
// 			if (is_string_in_array(result[i - 1], redirect) && i > 0)
// 			{
// 				i++;
// 				continue ;
// 			}
// 			ft_super_strcat(&result[first], " ");
// 			ft_super_strcat(&result[first], result[i]);
// 			free(result[i]);
// 			aux = delete_string(result, i);
// 			if (aux == NULL)
// 				return (NULL);
// 			free(result);
// 			result = aux;
// 			--i;
// 		}
// 		i++;
// 	}
// 	return (result);
// }

void	tokenize_state(t_shell *shell)
{
	t_parse_state	*state;

	char **res = pre_process_input(shell->input);
	int64_t i = 0;

	while (res[i] != NULL)
	{
		printf("res[%ld]: %s\n", i, res[i]);
		free(res[i]);
		i++;
	}
	free(res);
	shell->execute = exit_state;
	return;

	state = init_parse_state();
	while (shell->input[state->i])
	{
		if (!sub_tokenize(state, shell->input, shell))
			return ;
	}
	if (state->buf_index > 0)
	{
		state->buffer[state->buf_index] = '\0';
		add_token(&(shell->tokens), state->buffer);
	}
	free(state);
	shell->execute = assign_type_state;
}

// {
// }
