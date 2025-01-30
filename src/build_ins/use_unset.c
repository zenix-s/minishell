
#include "../../include/minishell.h"

static t_token	*prev(t_token **list_env, char *line)
{
	t_token	*l_aux;

	l_aux = *list_env;
	while (l_aux)
	{
		if (ft_strcmp ((char *)l_aux->next->content, line) != 0)
			l_aux = l_aux->next;
		else
			return (l_aux);
	}
	return (NULL);
}

//me da el nodo que estoy buscando para procesar su eliminación
static t_token	*search(t_token **list_env, char *line)
{
	t_token	*l_aux;
	char	*char_env;

	l_aux = *list_env;

	while (l_aux) 
	{
		char_env = (char *)l_aux->content;
		if (ft_strncmp(line, char_env, size_env(char_env)) == 0)
			return (l_aux);
		l_aux = l_aux->next;
	}
	return (NULL);
}

//para esta funcion necesito por ahora, que entre 
////line con unset y todas las cosas que va a eliminar
void	use_unset(t_token **list_env, char **line_arraid)
{
	int		count;
	t_token	*list_aux;
	t_token	*prev_aux;

	count = 1;
	while (line_arraid[count] != NULL)
	{
		list_aux = search(list_env, line_arraid[count]);
		if (list_aux)
		{
			prev_aux = prev(list_env, (char *)list_aux->content);
			if (prev_aux->next != NULL)
				prev_aux->next = prev_aux->next->next;
			else
				prev_aux->next = NULL;
		}
		free(list_aux->content);
		free(list_aux);
		list_aux = *list_env;
		count++;
	}
}
