
#include "../../include/minishell.h"
//TO DO

//los $ encanden el PID la variable, funciona como si no hubiese espacios...

static void	putvar(char *content)
{
	int		count;
	int		othercount;
	char	*linewrite;
	int		new_size;

	count = 0;
	othercount = 0;
	while (content[count] != '=')
		count++;
	count++;
	new_size = ft_strlen(content) - count;
	linewrite = (char *)ft_calloc(new_size + 1, sizeof(char));
	while (content[count])
	{
		linewrite[othercount] = content[count];
		count++;
		othercount++;
	}
	printf("%s ", linewrite);
	free(linewrite);
}

static void	onedolar(t_token *l_aux, char *line)
{
	char	*aux;
	char	*content;

	while (l_aux)
	{
		aux = ft_strtrim(line, "$");
		content = (char *) l_aux->content;
		if (ft_strncmp(content, aux, size_env(content)) == 0)
			putvar(content);
		free(aux);
		l_aux = l_aux->next;
	}
}

void	use_echo(t_token *list_env, char **line_arraid)
{
	t_token	*l_aux;
	int		arg;

	if (ft_strncmp(line_arraid[1], "-n", 1) == 0)
		arg = 2;
	else
		arg = 1;
	while (line_arraid[arg])
	{
		l_aux = list_env;
		if (line_arraid[arg][0] == '$' && line_arraid[arg][1] != '$')
			onedolar(l_aux, line_arraid[arg]);
		else
			printf("%s ", line_arraid[arg]);
		arg++;
	}
	if (ft_strncmp(line_arraid[1], "-n", 1) != 0)
		printf("\n");
}
