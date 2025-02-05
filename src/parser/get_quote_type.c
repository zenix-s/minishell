
#include "../../include/minishell.h"

t_quote	get_quote_type(t_quote quote_state, char c)
{
	if (c == '"' && quote_state != SINGLE)
	{
		if (quote_state == DOUBLE)
			quote_state = NONE;
		else
			quote_state = DOUBLE;
	}
	else if (c == '\'' && quote_state != DOUBLE)
	{
		if (quote_state == SINGLE)
			quote_state = NONE;
		else
			quote_state = SINGLE;
	}
	return (quote_state);
}
