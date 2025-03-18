#include "../include/minishell.h"

t_bool string_is_null_or_whitespace(const char *str)
{
	while (*str)
	{
		if (!is_space(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}
