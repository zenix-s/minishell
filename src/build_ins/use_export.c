
#include "../../include/minishell.h"

//idealmente aqui va a entrar VAR=valor
//es decir que no coge lo que le des
//no hace nada si hay comillas sin cerrar, en bash se queda como a la espera por decirlo asi
						// y luego mete todo a capon


static int	remplace(t_token **list_env, char *line)
{
	t_token	*l_aux;
	char	*content;

	l_aux = *list_env;
	while (l_aux)
	{
		content = (char *)l_aux->content;
		if (ft_strncmp(content, line, size_env(content)) == 0)
		{
			free(l_aux->content);
			l_aux->content = ft_strdup(line);
			return (0);
		}
		l_aux = l_aux->next;
	}
	return (1);
}
//cuando sergio te pase esto, este comando tiene que quitar las comillas...
static void	create_var(t_token **list_env, char *line)
{
	t_token	*new_node;

	new_node = ft_lstnew(ft_strdup(line));
	ft_lstadd_back(list_env, new_node);
}

void	use_export(t_token **list_env, char **line_arraid)
{
	int		count;
	int		value;

	count = 1;
	while (line_arraid[count])
	{
		value = remplace(list_env, line_arraid[count]);
		if (value == 1)
			create_var(list_env, line_arraid[count]);
		count++;
	}

//lo de arriba no es del todo asi, tiene el añadido de las funciones de sistema
}
