
#include "../../include/minishell.h"

void	here_doc(char **line_arraid, char *oldline)
{
	int		x;
	char	*line;
	int		texto;

	texto = open("file.txt", O_CREAT | O_WRONLY |O_APPEND, 0644);
	x = 0;
	while (x == 0)
	{
		line = readline("");
		if (line && *line != '\0')
		{
			if (ft_strcmp(line_arraid[1], line) == 0)
				x++;
			write(texto, line, ft_strlen(line));
			write(texto, "\n", 1);
		}
		free(line);
	}
	close(texto);
	unlink("file.txt");
}
