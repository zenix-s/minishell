
#include "../../include/minishell.h"

static int	get_quote_amount(char *str)
{
	int		amount;
	int		i;
	t_bool	can_count;
	t_quote	quote;

	amount = 0;
	can_count = FALSE;
	i = 0;
	quote = NONE;
	while (str[i])
	{
		quote = get_quote_type(quote, str[i]);
		if (quote != NONE)
			can_count = TRUE;
		if (quote == NONE && can_count)
		{
			amount++;
			can_count = FALSE;
		}
		i++;
	}
	if (quote != NONE)
		amount++;
	return (amount);
}

char	*remove_outer_quotes(char *str)
{
	char	*new_str;
	int		amount;
	int		i;
	int		j;
	t_quote	quote;

	amount = get_quote_amount(str);
	new_str = malloc(strlen(str) - (amount * 2) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	quote = NONE;
	while (str[i])
	{
		if ((quote == NONE && get_quote_type(quote, str[i]) != NONE)
			|| (quote != NONE && get_quote_type(quote, str[i]) == NONE))
			quote = get_quote_type(quote, str[i]);
		else
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
