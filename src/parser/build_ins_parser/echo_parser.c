
#include "../../../include/minishell.h"

char	*echo_parser(char *line)
{
	char	*new_line;
	t_quote	in_quotes;
	size_t	i;
	size_t	j;

	in_quotes = 0;
	i = 0;
	j = 0;
	new_line = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new_line)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '"' && in_quotes != SINGLE)
		{
			if (in_quotes == NONE)
				in_quotes = DOUBLE;
			else
				in_quotes = NONE;
		}
		else if (line[i] == '\'' && in_quotes != DOUBLE)
		{
			if (in_quotes == NONE)
				in_quotes = SINGLE;
			else
				in_quotes = NONE;
		}
		else if (line[i] == ' ' && in_quotes == NONE)
		{
			if (i > 0 && line[i - 1] != ' ')
				new_line[j++] = ' ';
		}
		else
			new_line[j++] = line[i];
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}
