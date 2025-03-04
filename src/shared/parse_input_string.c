
#include "../../include/minishell.h"
#include "../../include/parser.h"
#include <stdint.h>

// Push a string to an array of strings
// Allocate memory for the new string
int	push_string_to_array(char **arr, char *str)
{
	uint64_t	i;
	uint64_t	size;
	char		**new_arr;

	i = 0;
	size = 0;
	while (arr[size])
		size++;
	new_arr = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_arr)
		return (0);
	while (i < size)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = str;
	new_arr[i + 1] = NULL;
	free(arr);
	arr = new_arr;
	return (1);
}

//[hello "world hello" 'world hello' world]
// -->
// [hello] ["world hello"] ['world hello'] [world]
char	**parse_input_string(char *input)
{
	uint64_t	i;
	uint64_t	j;
	t_quote		quote_state;
	char		buffer[1024];
	char		**arr;

	i = 0;
	j = 0;
	quote_state = NONE;

	arr = (char **)malloc(sizeof(char *) * 1);
	if (!arr)
		return (NULL);
	arr[0] = NULL;

	while (input[i])
	{
		quote_state = get_quote_type(quote_state, input[i]);

		// Skip is_parse_space while outside quotes

		while (quote_state == NONE && is_parse_space(input[i]))
			i++;

		// while outside quotes and not is_parse_space push to buffer

		while (quote_state == NONE && !is_parse_space(input[i]))
		{
			buffer[j] = input[i];
			i++;
			j++;
		}

		if (quote_state == NONE && is_parse_space(input[i]))
		{
			buffer[i] = '\0';
			if (!push_string_to_array(arr, ft_strdup(buffer)))
				return (NULL);
			i = 0;
		}
		else
		{
			buffer[i] = input[i];
			i++;
		}
	}
}
