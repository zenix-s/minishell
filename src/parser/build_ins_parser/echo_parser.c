
#include "../../../include/minishell.h"
#include <stdio.h>

char	*echo_parser(char *line)
{
	char	*new_line;
	int		in_quotes;
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
		if (line[i] == '"' && in_quotes != 2)
		{
			if (in_quotes == 0)
				in_quotes = 1;
			else
				in_quotes = 0;
		}
		else if (line[i] == '\'' && in_quotes != 1)
			if (in_quotes == 0)
				in_quotes = 2;
			else
				in_quotes = 0;
		else
			new_line[j++] = line[i];
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}
