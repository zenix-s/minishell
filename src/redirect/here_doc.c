
#include "../../include/minishell.h"

void	foo_here_doc(char **line_arraid)
{
	int		x;
	char	*line;
	int		text;

	text = open("file.txt", O_CREAT | O_WRONLY |O_APPEND, 0644);
	x = 0;
	while (x == 0)
	{
		line = readline("");
		if (line && *line != '\0')
		{
			if (ft_strcmp(line_arraid[0], line) == 0)
				x++;
			write(text, line, ft_strlen(line));
			write(text, "\n", 1);
		}
		free(line);
	}
	close(text);
	unlink("file.txt");
	ft_free(line_arraid);
}
